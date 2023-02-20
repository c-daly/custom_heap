#include <stdio.h>
#include "pm_heap.h"

static block_header_t base;
static block_header_t* freep = NULL;
void* allocated_mem[NALLOC];

/*void init_pm_heap() {

}*/

void* pm_malloc(int size) {
  block_header_t *p, *prevp;
  /* 
   * This gives us the size of the requested
   * memory in terms of header-sized chunks.
   * See K&R 8.7 for details.
   */
  int nunits =
    (size + sizeof(block_header_t) - 1) /
      sizeof(block_header_t) + 1;

  if((prevp = freep) == NULL) {
    /* no list yet */
    base.next = freep = prevp = &base;
    base.size = 0;
    base.payload = allocated_mem;
  }

  

  /* iterate over the list */
  for(p = prevp->next;;prevp = p, p = p->next) {
    if(p->size >= nunits) {
      if(p->size == nunits) {
        prevp->next = p->next;
      } 
      else {
        p->size -= nunits;
        p += p->size;
        p->size = nunits;
      }
      freep = prevp;
      printf("Returning a pointer");
      return (void*) (p+1);
    }
    /* Made it all the way back to the head of the list */
    if(p == freep && p->size != 0) {
      printf("Couldn't find any");
      return NULL;
      /* We're at the head of the list but it's because it's
       * our first time through */
    } else if(p == freep) {
      printf("Need to divide base up for first allocation");
      p->size = nunits;
      p->payload = base.payload + nunits;
      p->size = NALLOC - nunits;

      return (void*)(p->payload);
    }
  }
}

void pm_free(void* ptr) {
}
