#ifndef PM_HEAP_H
#define PM_HEAP_H

/* 10MB */
#define NALLOC 1024

/*
 * Acts as a descriptor for each
 * block of memory, holding the size
 * and a pointer to the next free 
 * block.
 */
typedef struct block_header_t {
  unsigned int size;
  void* payload;
  struct block_header_t* next;
} block_header_t;

void* pm_malloc(int size);
void pm_free(void* ptr);
#endif
