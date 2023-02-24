#include <stdio.h>
#include "pm_heap.h"
#include "../linkedlist/linkedlist.h"
/* initial memory usage with the default initialized
 * linked list is 64.  Requests are satisfied with 
 * the size requested + the size of the header block.
 * In our case, a pm_malloc(16) would cause the starting
 * memory allocation to be 96 bytes.
 */ 
static block_header_t base;
static block_header_t temp_block;
static node_t* free_list = NULL;
static node_t temp_element;
static node_t* first_node;
static block_header_t* freep = NULL;
static block_header_t* first_header = NULL;
int block_size = sizeof(block_header_t);
int init_complete = 0;
int heap_size;
void* allocated_mem[NALLOC];
static block_header_t* temp_header;

void init_heap() {
  int allocated_so_far = 0;
  free_list = (node_t*) (allocated_mem);
  allocated_so_far += sizeof(node_t);
  first_header = (block_header_t*) (allocated_mem + allocated_so_far);
  allocated_so_far += sizeof(block_header_t);
  first_node = (node_t*)(allocated_mem + allocated_so_far);
  allocated_so_far += sizeof(node_t);
  first_header->size = NALLOC - allocated_so_far;
  first_header->ptr = (void*) (first_header + sizeof(block_header_t));
  first_node->data = first_header;
  //freep = first_header;
  add_node_to_tail(free_list, first_node);
  heap_size = allocated_so_far;
  init_complete = 1;
  printf("Sizeof(node_t): %ld", sizeof(node_t));
  printf("allocated: %d\n", allocated_so_far);
  printf("backing array: %p\n", allocated_mem);
}

void print_free_list() {
  node_t* tp = free_list->next;

  while(tp->data) {
    block_header_t* header = (block_header_t*) free_list->data;
    if(header) {
      printf("Size: %d\n", header->size);
    }
    tp = tp->next; 
  }

}
void* pm_malloc(int size) {
  printf("SIZE: %d\n", size);
  if((heap_size + size + block_size) > NALLOC) {
    printf("OUT OF MEMORY\n");
    return NULL;
  }

  block_header_t *p, *prevp, *header;
  if(!init_complete) {
    init_heap();
  }
  node_t* tp = free_list->next;

  while(tp->data) {
    header = tp->data;
    printf("Header size: %d\n", header->size);
    if(header->size >= (size + sizeof(block_header_t))) {
      //block_header_t* temp_header;
      header->size -= (size + sizeof(block_header_t));   
      heap_size += (size + sizeof(block_header_t));
      freep = (block_header_t*) (allocated_mem +
          (heap_size - size - sizeof(block_header_t)));
      freep->size = size + sizeof(block_header_t);
      freep->ptr = (void*)(freep + sizeof(block_header_t));
      return (void*) (freep + block_size); //freep->ptr;
    }
    printf("hit next");
    tp = tp->next;
  }
  printf("Memory not found");
  return NULL;
}

void pm_free(void* ptr) {
  node_t tempNode;

  temp_header = (block_header_t*) (ptr - sizeof(block_header_t));
  heap_size -= (temp_header->size + block_size);
  //add_node_to_tail(free_list, &tempNode);
  enqueue(free_list, temp_header);
  printf("%d\n", qsize(free_list));
}
