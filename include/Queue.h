#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>
#include "List.h"
/**
 *  Purpose: this struct represent the data structure Queue as an array.
 *  @elements   array of pointers to the actual data objects.
 *  @len        the number of elements currently in the Queue.
 *  @cap  
 **/
struct Queue
{
    struct SLList* list;
    const uint32_t *const len;
};

/**
 * Purpose: this function is used to make Queue objects.
 * @freeElement         is the freeing funciton to use when removing the element 
 *                      from the Queue, or the whole Queue as a whole.
 */
struct Queue* makeQueue(void (*freeElement)(void*));

/**
 * Purpose: this function is used to free the Queue and the underlying
 *          Singly Linked List.
 * @queue   is the queue wanted to be free.
 */
void freeQueue(struct Queue* queue);

/**
 *  Purpose: this function is used to add a data element to the Queue.
 *  @queue      the queue we want to insert the element into it.
 *  @data       pointer to the data object to be inserted.
 **/
void Enqueue(struct Queue* queue, void* data);

/**
 * Purpose: this function it used to get the head of the Queue out of it.
 * @queue       the Queue we want to dequeue.
 *
 * NOTE: it's the caller responsiblity to free the returned address by the 
 *       appropriate freeing function.
 * */
void* Dequeue(struct Queue* queue);

#endif
