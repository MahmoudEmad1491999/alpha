#include "Tree.h"
#include "HelperFuncs.h"
#include "Macros.h"
#include "Queue.h"
#include "Stack.h"

void BreadthTraverse(struct TreeNode *root, void (*hook)(void *))
{
    if(root)
    {
        struct Queue* toBeTraversed = makeQueue(NULL);    
        Enqueue(toBeTraversed, root);
        struct TreeNode* temp;
        while(*toBeTraversed->len)
        {
            temp = Dequeue(toBeTraversed);     
            hook(temp->data);
            for(uint32_t index = 0; index < temp->degree; index++)
            {
                if(temp->children[index])
                {
                    Enqueue(toBeTraversed, temp->children[index]);
                }
            }
        }
        freeQueue(toBeTraversed);
    }
}

void PreOrderTraverse(struct TreeNode *root, void (*hook)(void *))
{
    if(root)
    {
        // construct a stack to hold the next child on the top of it.
        struct Stack *toBeTraversed = makeStack(NULL);
        // push the root on top of the stack.
        Push(toBeTraversed, root);
        struct TreeNode *temp;
        // keep looping until the stack is empty.
        while (*toBeTraversed->len) {
            // pop the next child to be traversed from the stack
            temp = Pop(toBeTraversed);
            // call the hook function using the data payload of the head
            // of the stack.
            hook(temp->data);
            // add the childred of the popped out node to the stack from right
            // to left so that the top of the stack is the left most child of
            // the previous head of the stack.
            for (uint32_t index = 0; index < temp->degree; index++) {
                // if the child is present and not null push it to the stack.
                if (temp->children[temp->degree - 1 - index]) {
                    Push(toBeTraversed,
                         temp->children[temp->degree - 1 - index]);
                }
            }
        }
        freeStack(toBeTraversed);
    }
}

void InOrderTraverse(struct TreeNode *root, void (*hook)(void *))
{
    if (root) {
        // this is the stack which will always hold the next node
        // to be called on by the hook on the top.
        struct Stack *toBeTraversed = makeStack(NULL);
        struct TreeNode *current = NULL;
        struct TreeNode *popped_node = NULL;
        // set the current to the root.
        current = root;

        while(current != NULL || *toBeTraversed->len != 0){
            while(current) {
                // keep looping until the left most branch is stored into the stack.
                // if the current has more childs than 2.
                if (current->degree > 2) {
                    FAIL("InOrderTraverse Method can only work with trees of "
                         "degree of 2 or less.");
                }
                // push the current node on top of the stack.
                Push(toBeTraversed, current);
                // set the current to the left node of the current node.
                current = current->children[0];
            };
            // if current is null and the length of the stack is not empty
            if (current == NULL && *toBeTraversed->len != 0) {
                // pop the top of the stack.
                popped_node = Pop(toBeTraversed);
                // visit the popped node.
                hook(popped_node->data);
                // set the current node to the right of the current node.
                current = popped_node->children[1];
            }
        };
    }
}

void PostOrderTraverse(struct TreeNode *root, void (*hook)(void *))
{
    // the is the stack that is going to hold the next node to be handled. 
    struct Stack* toBeTraversed = makeStack(NULL);
    // this stack is holding the order of traversing the tree in reverse.
    struct Stack* output = makeStack(NULL);
    // push the root node onto the toBeTraversed Stack.
    Push(toBeTraversed, root);

    struct TreeNode* temp = NULL;
    while(*toBeTraversed->len)
    {
        // pop the head of the stack out.
        temp = Pop(toBeTraversed);
        // push it onto the output stack.
        Push(output, temp);
        // add it's children to the toBeTraversed stack so that it can be
        // handled.
        for(uint32_t index = 0; index < temp->degree; index++)
        {
            // add only the child if it's not NULL.
            if(temp->children[temp->degree-1 - index])
            {
                Push(toBeTraversed, temp->children[temp->degree-1 - index]);
            }
        }
    }

    while(*output->len)
    {
        hook(Pop(output));
    }

}

