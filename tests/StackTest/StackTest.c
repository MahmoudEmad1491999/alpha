#include "Stack.h"
#include "HelperFuncs.h"
#include <stdlib.h>


int main(int argc, char** argv)
{
    struct Stack* stack = makeStack(free);
    int* x = xmalloc(sizeof(int));
    *x = 200;        
    Push(stack, x);

    printf("%d\n", *(int*)(Pop(stack)));
    printf("%d\n", *(stack->len));
    free(x);
    freeStack(stack);
    return 0;
}

