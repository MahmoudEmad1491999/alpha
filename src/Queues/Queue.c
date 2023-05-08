#include "Queue.h"
#include "HelperFuncs.h"
#include "List.h"
#include <stdlib.h>

void Enqueue(struct Queue* queue, void* data)
{
    SLListAppend(queue->list, data);
}

void* Dequeue(struct Queue *queue) {
    // this value is to get the deleted varaible from the first of the array.
    void* out;
    SLListDelete(queue->list, 0, &out);
    return out;
}

struct Queue* makeQueue(void (*freeElement)(void*))
{
    struct Queue* queue = xmalloc(sizeof(struct Queue));
    queue->list = makeSLList(freeElement);
    // cast the len member of the queue to a pointer to pointer to uint32_t and assign it
    // the address of the len member of the underlying queue.
    *(uint32_t**) &(queue->len) = &(queue->list->len);
    return queue;
}

void freeQueue(struct Queue* queue)
{
    if(queue)
    {
        freeSLList(queue->list);
        free(queue);
    }
}
