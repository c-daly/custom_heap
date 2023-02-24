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
  node_t* newNode = pm_malloc(sizeof(node_t));
  node_t* oldTail = list->prev;

  newNode->data = element;
  newNode->next = list;
  /* oldTail might be NULL, but that's ok */
  newNode->prev = oldTail;
  
  list->prev = newNode;

  /* This might be the first node */
  if(!list->next) {
    list->data = NULL;
    list->next = newNode;
    newNode->prev = list;
  }
  /* not ok for oldTail to be NULL here
     when we set its next to the new tail */
  if(oldTail)
    oldTail->next = newNode;

  return list;
}

node_t* add_node_to_tail(node_t* list, node_t* new_node) {
  node_t* prevTail = list->prev;
  new_node->next = list;
  list->prev = new_node;
  if(!prevTail) {
    new_node->prev = list;
    list->next = new_node;
  } else {
    new_node->prev = prevTail;
    prevTail->next = new_node;
  }
  return list;
}

/* 
 * Pulls items off front of list
 *
 * @param list: list we're removing items from
 */
void* delist(node_t* list) {
  /* no work to do */
  if(!list || !(list->next))
    return NULL;

  node_t* oldHead = list->next;
  node_t* newHead = oldHead->next;
  void* data = oldHead->data;

  newHead->prev = list;
  free(oldHead);

  return data;
}
/* 
 * Helper function to extract next highest priority
 * item from the list.
 *
 * @param list: the list that holds the priority
 *               elements.
 */
node_t* getNextPriorityElement(node_t* list) {
  node_t* hpElement = list->next;
  node_t* tp = list->next;
  process_t* process = tp->data;
  int currentHighPriority = process->priority;

  while(tp->data) {
    process = tp->data;
    if(process->priority > currentHighPriority) {
      currentHighPriority = process->priority;
      hpElement = tp;
    }
    tp = tp->next;
  }

  return hpElement;
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

