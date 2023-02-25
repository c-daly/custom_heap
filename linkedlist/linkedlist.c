/*
 * queue.c / Process Queue
 * 
 * Christopher Daly / CS5600 / Northeastern University
 * Spring 2023 / Jan 25
 */
#include "linkedlist.h"
#include "../heap/pm_heap.h"

/*
 * Adds new data elements to end of list
 *
 * @param list: list we're adding to
 * @param element: data element to store 
 */
node_t* enqueue(node_t* list, void* element) {
  if(list->data) {
    printf("LIST DATA NOT NULL!");
  }
  printf("\ninvoking pm_malloc from enqueue");
  node_t* newNode = pm_malloc(sizeof(node_t));
  if(!newNode) {
    printf("pm_malloc failed to allocate memory. aborting\n");
    return NULL;
  }

  list->prev->next = newNode;
  newNode->next = list;
  newNode->prev = list->prev;
  newNode->data = element;
  
  node_t* oldTail = list->prev;
  //oldTail->next = newNode;
  list->prev = newNode;
  return list;
}

//TODO: change name to reflect this method is only called
//because enqueue is called in pm_malloc. Call it something
//like initialize_list_with_node.  Everywhere else enqueue is used.
node_t* add_node_to_tail(node_t* list, node_t* new_node) {
  list->data = NULL;
  node_t* prevTail = list->prev;

  new_node->next = list;
  new_node->prev = list;

  list->prev = new_node;
  list->next = new_node;
 
  return list;
}

/* 
 * Pulls items off front of list
 *
 * @param list: list we're removing items from
 */
void* delist(node_t* node) {
  /* no work */
  if(!node) {
    return NULL;
  } else if(node->prev == node->next) {
  /* if previous equals next, it
   * means we only have two elements
   * and we can just null out the 
   * next/prev pointers on list
   */
    node->prev->next = NULL;
    node->next->prev == NULL;
    return NULL;
  } else {

    node_t* prev_node = node->prev;
    node_t* next_node = node->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;
    //node_t* oldHead = list->next;
    //node_t* oldTail = list->prev;

    //node_t* newHead = oldHead->next;
    //void* data = oldHead->data;

    return node;
  }
}

/*
 * Method reports the number of elements currently
 * in the list.
 *
 * @param list:  list we're sizing.
 */
int qsize(node_t* list) {
  if(!list->next)
    return 0;

  node_t* tempPtr = list->next;
  int size = 0;

  while(tempPtr->data) {
    size++;
    tempPtr = tempPtr->next;  
  }

  return size;
}

void freeQueue(node_t* list) {
  node_t* temp;
  while(qsize(list) > 0) {
    temp = list;
    list = list->next;
    free(temp);
  }

  if(list) {
    free(list);
  }
}

