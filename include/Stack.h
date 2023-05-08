#ifndef STACK_H
#define STACK_H
#include "List.h"

/**
 * Purpose: this strucutre represent a stack datastructure.
 * @list    pointer to the underlying list datasturcture used to
 *          implement the Stack behavior.
 * @len     is a const pointer to a const number which is always pointing
 *          to the len memeber of the underlying list.
 */
struct Stack
{
    struct SLList* list;    
    const uint32_t * const len;
};


/**
 * Purpose: this function is used to push the data object pointed by
 *          @data into the stack.
 * @stack   is the stack to push into.
 * @data    pointer to the data object.
 */
void Push(struct Stack* stack, void* data);

/**
 * Purpose: this function is used to pop  the data object out of Stack object.
 * @stack   is the stack to pop out of.
 * @return  pointer to the data object on the head of the stack.
 */
void* Pop(struct Stack* stack);
/**
 * Purpose: this function is used to make a new Stack object.
 * @freeElement     the function used to free the data object.
 */
struct Stack* makeStack(void (*freeElement)());
/**
 * Purpose: this function is used to free the stack object and the remaining underlying
 *          list items.
 * @stack   the stack to be freed.
 */
void freeStack(struct Stack* stack);
#endif
