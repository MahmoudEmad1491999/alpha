#include "HelperFuncs.h"
#include "Macros.h"
#include "Queue.h"
#include "Stack.h"
#include "Tree.h"

struct TreeNode *makeTreeNode(struct TreeNode* parent,void *data, uint32_t degree) {
    struct TreeNode *treeNode = xmalloc(sizeof(struct TreeNode));
    // assign the parent of the node to the parent member.
    treeNode->parent = parent;
    // assign the data and degree of the node.
    treeNode->data = data;
    treeNode->degree = degree;
    // if the degree is not zero then allocate a space for the array of pointers
    // and assign them to null.
    if (degree) {
        // create an array of pointers to other nodes only if degree is not 0.
        treeNode->children = xcalloc(degree, sizeof(struct TreeNode *));
    }

    return treeNode;
}

// level based traversal.
void BreadthTraverse(struct TreeNode *root, void (*hook)(struct TreeNode *)) {
    if (root) {
        // create a new queue.
        struct Queue *toBeTraversed = makeQueue(NULL);
        // add the root to the queue
        Enqueue(toBeTraversed, root);
        struct TreeNode *temp;
        // while the queue is not empty 
        while (*toBeTraversed->len) {
            // dequeue the element from the queue which is also the next inline 
            // to be traversed by the hook function.
            temp = Dequeue(toBeTraversed);
            // call the hook function on the next in line node data payload.
            hook(temp);
            // loop on the children of the next in line node,
            // if they exist add them to the queue if not skip.
            for (uint32_t index = 0; index < temp->degree; index++) {
                if (temp->children[index]) {
                    Enqueue(toBeTraversed, temp->children[index]);
                }
            }
        } // loop till the queue is empty.
        // free the Queue Object.
        freeQueue(toBeTraversed);
    }
}

// preorder traversal of the tree nodes.
void PreOrderTraverse(struct TreeNode *root, void (*hook)(struct TreeNode *)) {
    if (root) {
        // call the hook function on the data payload of the root node.
        hook(root);
        // for each child node call the PreOrderTraverse method,
        // of course if the child is not NULL.
        for (uint32_t index = 0; index < root->degree; index++) {
            // if the child is null just pass.
            if (root->children[index]) {
                PreOrderTraverse(root->children[index], hook);
            }
        }
    }
}
// postorder traversal of the tree nodes.
void PostOrderTraverse(struct TreeNode *root, void (*hook)(struct TreeNode*)) {
    if (root) {
        // call the PostOrderTraverse method on each child node of the root.
        // of course if it's not NULL.
        for (uint32_t index = 0; index < root->degree; index++) {
            // if the child is NULL pass.
            if (root->children[index]) {
                PostOrderTraverse(root->children[index], hook);
            }
        }
        // call hook on the payload of root node.
        hook(root);
    }
}
// inorder traverse of the tree nodes.
void InOrderTraverse(struct TreeNode *root, void (*hook)(struct TreeNode *)) {
    if (root) {
        // fail if the root node's degree is not 2.
        if (root->degree != 2) {
            FAIL(
                "InOrderTraverse does only make sense with trees of 2 degrees");
        }
        // traverse the left subtree first.
        if (root->children[0]) {
            InOrderTraverse(root->children[0], hook);
        }
        // call the hook function on the data payload second.
        hook(root);
        // traverse the right subtree third
        if (root->children[1]) {
            InOrderTraverse(root->children[1], hook);
        }
    }
}
