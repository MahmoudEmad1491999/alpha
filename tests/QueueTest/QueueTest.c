#include "Queue.h"
#include "HelperFuncs.h"

int main(int argc, char** argv)
{
    struct Queue* queue = makeQueue(free);
    
    int*x = xmalloc(sizeof(int));
    *x = 100;

    int*y = xmalloc(sizeof(int));
    *y = 200;

    int*z = xmalloc(sizeof(int));
    *z = 300;
    
    Enqueue(queue,x);
    Enqueue(queue,y);
    Enqueue(queue,z);

    printf("%d\n", *(int*)(Dequeue(queue)));
    printf("%d\n", *(queue->len));
    printf("%d\n", *(int*)(Dequeue(queue)));
    printf("%d\n", *(queue->len));
    printf("%d\n", *(int*)(Dequeue(queue)));
    printf("%d\n", *(queue->len));

    free(x);
    free(y);
    free(z);
    freeQueue(queue);
    return 0;
}
