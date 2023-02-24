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
int node_size = sizeof(node_size);
int init_complete = 0;
int heap_size;
void* allocated_mem[NALLOC];
static block_header_t* temp_header;

/* this function just needs to create
 * the free_list
 */
void init_heap() {
  /* good idea to keep a running total of allocated memory */
  int allocated_so_far = 0;
  /* root of our free memory list */
  free_list = (node_t*) (allocated_mem);
  allocated_so_far += sizeof(node_t);
  
  /* first head for our (currently) only chunk of memory */
  first_header = (block_header_t*) (allocated_mem + allocated_so_far);
  first_header->size = NALLOC - allocated_so_far;
  first_header->ptr = (void*) (first_header + sizeof(block_header_t));
  allocated_so_far += sizeof(block_header_t);

  /* first data-holding element of free_list. 
   * We're allocating this memory even though no
   * one asked for it.  This is a recurring addional
   * expense to the header structure.  When elements
   * are freed, new nodes must be created.
   * Note that it is basically pm_malloc'ing itself
   * some memory because we can't call pm_malloc from this
   * function.
   */ 
  first_node = (node_t*)(allocated_mem + allocated_so_far);

  allocated_so_far += sizeof(node_t);
  first_node->data = first_header;
  first_node->prev = first_node;
  first_node->next = first_node;
  
  //freep = first_header;
  add_node_to_tail(free_list, first_node);
  heap_size = allocated_so_far;
  printf("%d bytes allocated for first node and first header\n", allocated_so_far);
  init_complete = 1;
}

void print_free_list() {
  printf("Printing List:\n");
  node_t* tp = free_list->next;

  while(tp->data != NULL) {
    //block_header_t* header = ((block_header_t*) (tp - sizeof(block_header_t)));
    block_header_t* header = (block_header_t*) tp->data;
    printf("Size: %d  Next: %p\n", header->size, header->ptr);
    tp = tp->next; 
  }

}
void* pm_malloc(int size) {
  block_header_t *p, *prevp, *header;
  if(init_complete == 0) {
    init_heap();
  }
  node_t* tp = free_list->next;

  while(tp->data) {
    header = tp->data;
    if(header->size >= (size + sizeof(block_header_t))) {
      if((allocated_mem + 16 + size) > (allocated_mem + NALLOC)) {
        printf("SEGFAULT ABORTING!");
        return NULL;
      }
      //block_header_t* temp_header;
      header->size -= (size + sizeof(block_header_t));   
      heap_size += (size + sizeof(block_header_t));
      freep = (block_header_t*) (allocated_mem + (heap_size - size - sizeof(block_header_t)));
      freep->size = size + sizeof(block_header_t);
      freep->ptr = (void*)(freep + sizeof(block_header_t));
      printf("allocating %d bytes\n", freep->size);
      return freep->ptr;
    }
    tp = tp->next;
  }
  printf("Memory not found");
  return NULL;
}

void pm_free(void* ptr) {
  node_t tempNode;

  temp_header = ((block_header_t*)ptr - sizeof(block_header_t));
  heap_size -= (temp_header->size + block_size);
  //add_node_to_tail(free_list, &tempNode);
  enqueue(free_list, temp_header);
  print_free_list();
}
