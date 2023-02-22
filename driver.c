#include "heap/pm_heap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // init pm_heap
  // pm_malloc (a few different times)
  // pm_free
  //void *new_ptr, *new_ptr2, *new_ptr3;
  //new_ptr = pm_malloc(1024);
  //pm_free(new_ptr);
  //new_ptr2 = pm_malloc(1024);
  
  //pm_free(new_ptr2);
  //new_ptr3 = pm_malloc(1024);
  //pm_free(new_ptr3);
  void *new_ptr;
  int heap_size;
  for(int x = 0; x < 10; x++) {
    new_ptr = pm_malloc(1024);
    //heap_size += 1024;

    printf("%d: %p\n", x, new_ptr);
    pm_free(new_ptr);
  }
  return 0;
}
