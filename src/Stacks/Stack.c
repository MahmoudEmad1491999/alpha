#include "Stack.h"
#include "HelperFuncs.h"
#include "List.h"
#include "Macros.h"

struct Stack* makeStack(void (*freeElement)(void*))
{
    struct Stack* stack = xmalloc(sizeof(struct Stack));
    stack->list = makeSLList(freeElement);
    *((uint32_t**)&(stack->len)) = &(stack->list->len);
    return stack;
}


void freeStack(struct Stack *stack)
{
    if(stack)
    {
        freeSLList(stack->list);
        free(stack);
    }
}
void Push(struct Stack* stack, void* data)
{
    FAIL_IF_NULL(stack);
    SLListAppend(stack->list, data);
}

void const* Pop(struct Stack *stack) {
    // check if the stack is null.
    FAIL_IF_NULL(stack);
    // check if the stack is empty, and return -1 if so.
    if (*stack->len == 0){
        FAIL("Cannot pop out of a empty stack.");
    }
    else {
        void* out;
        SLListDelete(stack->list, stack->list->len - 1, &out);
        return out;
    }
}


