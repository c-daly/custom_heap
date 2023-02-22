#include <stdio.h>
#include <string.h>
#include "pm_heap.h"

static block_header_t* freep = NULL;
static block_header_t* head = NULL;
static block_header_t* tail = NULL;
static block_header_t initial_block;
static int heap_size = 0;
char allocated_mem[NALLOC] = {0};
static unsigned int nalloc_as_nunits = (NALLOC - 1)/(sizeof(block_header_t) + 1);

void init_heap() {
  block_header_t temp_block;
  initial_block.size = NALLOC; //nalloc_as_nunits;
  initial_block.next = NULL;
  freep = head = &initial_block;
  memcpy(allocated_mem, freep, sizeof(block_header_t));

}
void* pm_malloc(int size) {
  if(size + heap_size > NALLOC) {
    printf("ERROR: out of memory\n");
    return NULL;
  }
  block_header_t temp_block;
  block_header_t *p, *prev_tb, *tb;

  if(!freep) {
    init_heap();
  }

  /* don't loop if we don't have to */
  if(freep->size > size) {
    temp_block.size = size;
    temp_block.next = NULL;
    
    freep->size -= size;
    heap_size += size;
    memcpy((allocated_mem + heap_size), &temp_block, sizeof(block_header_t));
    return (void*) (allocated_mem + heap_size + sizeof(block_header_t));
  }

  /* traversal block */
  tb = freep;

  while(tb) {
    /* this block could fit it */
    if(tb->size >= size) {   
      tb->size -= size;
      heap_size += size;
      temp_block.size = size; 
      if(tb->next) {
        block_header_t* next = tb->next;
        temp_block.next = &next;
      }
      tb->next = temp_block;
      //if(!tb->next) {
      //  memcpy((allocated_mem + heap_size), tb, sizeof(block_header_t));
      //  tb->next = NULL;
      //  freep = tb;
      //  return (void*) (allocated_mem + heap_size + sizeof(block_header_t));
      //}
    
      memcpy((allocated_mem + heap_size), &temp_block, sizeof(block_header_t));
      freep = tb;
      return (void*) (allocated_mem + heap_size + sizeof(block_header_t));
    }

    //if(!tb->next) {
    //  break;
    //}
    //prev_tb = tb;
    tb = tb->next;
  }
  return NULL;
}

void pm_free(void* ptr) {
  block_header_t temp_block;
  block_header_t* tb = freep;

  if(!freep->next) {
    block_header_t* header = ((block_header_t*) (ptr - sizeof(block_header_t)));
    tb->size = sizeof(block_header_t) + header->size;
    tb->next = ((block_header_t*) (ptr - sizeof(block_header_t)));
  }
  //while(tb->next && tb->size > 0) {
  //  printf("stuck\n");
  //  tb = tb->next;
  //}
  return;
}
