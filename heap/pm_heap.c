#include <stdio.h>
#include <pthread.h>
#include "pm_heap.h"
#include "../linkedlist/linkedlist.h"

/* initial memory usage with the default initialized
 * linked list is 64 (two headers and one node == 64).
 * Requests are satisfied with the size requested +
 * the size of the header block. In our case, a 
 * pm_malloc(16) would add 32 (header_size + size) */ 
static node_t* free_list = NULL;

int header_size = sizeof(block_header_t);
int node_size = sizeof(node_t); 

static block_header_t* freep = NULL;
static block_header_t* first_header = NULL;
static node_t* first_node;

pthread_mutex_t lock;

void* allocated_mem[NALLOC];
void* max_address = (void*)allocated_mem + NALLOC;

/* this function just needs to create
 * the free_list, which will consist of
 * a head node with no data, and a second node
 * where the data is the region of memory not
 * yet allocated for nodes or headers
 * (NALLOC - allocated_so_far)
 */
void init_heap() {
  //int allocated_so_far = 0;

  /* root of our free memory list 
   * This node will come from the overall 
   * memory allotment and will never be
   * available for allocation.
   * This differs from subsequent nodes
   * which are included in the size figures
   * on their headers */
  free_list = (node_t*) (allocated_mem);

  
  /* first header for our (currently) only chunk of memory */
  first_header = (void*)free_list + node_size;
  first_header->size = NALLOC - node_size; //allocated_so_far;
  first_header->ptr = (void*)first_header + sizeof(block_header_t);

  /* first data-holding element of free_list. 
   * We're allocating this memory even though no
   * one asked for it.  This is a recurring addional
   * expense to the header structure.  When elements
   * are freed, new nodes must be created.
   * Note that it is basically pm_malloc'ing itself
   * some memory because we can't call pm_malloc from this
   * function.
   */ 
  first_node = (node_t*)first_header + header_size;

  first_node->data = first_header;
  first_node->prev = first_node;
  first_node->next = first_node;
  
  /* this function allows us to avoid calling pm_malloc
   * before our list is created */
  add_node_to_tail(free_list, first_node);
}

/* debug method */
void print_free_list() {
  node_t* tp = free_list->next;

  printf("\nfree_list state:\n****************");
  printf("\nList size: %d", qsize(free_list));
  printf("\nList header: %p", free_list);
  while(tp->data != NULL) {
    block_header_t* header = (block_header_t*) tp->data;
    if(header && header->size && header->ptr) {
      printf("\n(header data)ptr: %p\n(node data)Next: %p, Prev: %p, this: %p\n", 
          header->ptr,
          tp->next,
          tp->prev,
          tp);
    } else {
      printf("header data NULL");
    }
    tp = tp->next; 
  }
  printf("\n");
}

void* pm_malloc(int size) {
  block_header_t *header;

  if(!freep) {
    init_heap();
  }
  node_t* tp = free_list->next;

  pthread_mutex_lock(&lock);
  while(tp->data) {
    header = tp->data;

    if(header->size > (size + header_size)) {

      int total_new_size = size + header_size;
      header->size -= total_new_size;  
      freep = (void*)header + header->size;
      freep->size = size + header_size;
      freep->ptr = (void*)freep + sizeof(block_header_t);

      if(((void*)freep + freep->size) > max_address) {
        pthread_mutex_unlock(&lock);
        return NULL;
      }
      pthread_mutex_unlock(&lock);
      return freep->ptr; //freep->ptr;
    }
    tp = tp->next;
  }
  pthread_mutex_unlock(&lock);
  return NULL;
}

void pm_free(void* ptr) {
  if(!ptr) {
    return;
  } else {

    pthread_mutex_lock(&lock);
    block_header_t* temp_header = (void*)ptr - sizeof(block_header_t);
     
    node_t* temp_node = (node_t*) (temp_header->ptr);
    temp_node->data =  (void*)ptr - sizeof(block_header_t);//temp_header;
    add_node_to_tail(free_list, temp_node);
    pthread_mutex_unlock(&lock);
  }
}
