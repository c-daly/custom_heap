#include "heap/pm_heap.h"
#include "linkedlist/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // init pm_heap
  // pm_malloc (a few different times)
  // pm_free
  void* tempPtr;
  void* tempPtr2;
 
  for(int x = 0;x<=28;x++) {
   block_header_t* header;
    tempPtr = pm_malloc(16);
    if(tempPtr) {
      header = ((block_header_t*) tempPtr - sizeof(block_header_t));
      pm_free(tempPtr);
    }

    tempPtr2 = pm_malloc(8);
  }
  print_free_list();
  //node_t* head;
  //node_t* middle;
  //node_t* tail;
  //head = pm_malloc(sizeof(node_t));
  //middle = pm_malloc(sizeof(node_t));
  //tail = pm_malloc(sizeof(node_t));
  //pm_free(middle);
  //printf("%p\n", head);
  return 0;
}
