#include "BST.h"
#include "HelperFuncs.h"
#include "Macros.h"

struct BstNode* makeBSTNode(void* data)
{
    struct BstNode* root = xmalloc(sizeof(struct BstNode));
    root->parent = NULL;
    root->data = data;
    root->children[0] = NULL;
    root->children[1] = NULL;
    return root;
}

void addElementToBST(struct BstNode *bst, void *data, int8_t (*compare)(void *, void *))
{
    // first we need to check if the given binary search tree pointer is not null.
    FAIL_IF_NULL(bst);
    
    // compare the given data to the data payload of bst. 
    int8_t compare_result = compare(data, bst->data);
    
    if(compare_result == 1)
    {
        // if the compare result is 1, this means that the new data is going to
        // be in a node on the right subtree of bst.

        if(bst->children[1]) // if the right child is present.
        {
            addElementToBST(bst->children[1], data, compare);
        }
        else // if the right child is not present.
        {
            struct BstNode* new_node = makeBSTNode(data);
            new_node->parent = bst;
            bst->children[1] = new_node;
        }
    }
    else if(compare_result == -1)
    {
        // if the compare result is -1, this means that the new data is going to
        // be in a node on the left subtree of bst.

        if(bst->children[0]) // if the right child is present.
        {
            addElementToBST(bst->children[0], data, compare);
        }
        else // if the right child is not present.
        {
            struct BstNode* new_node = makeBSTNode(data);
            new_node->parent = bst;
            bst->children[0] = new_node;
        }
    } else {
        // this means compare result is zero and bst is actually holding data payload equvilant to the given data.
        // so return.
        return; 
    }
    
}

struct BstNode* searchElementBST(struct BstNode *bst, void *data, int8_t (*compare)(void* data1, void* data2))
{
    // there is no meaning in searching a null binary search tree.
    // but this does not mean that we cannot return NULL.
    FAIL_IF_NULL(bst);
    int8_t compare_result = compare(data, bst->data);
    if(compare_result == 1)
    {
        // this means that data is going be on the right subtree of bst.
        if(bst->children[1])
        {
            searchElementBST(bst->children[1],data, compare);
        }
        else {
            return NULL;
        }
    }
    else if(compare_result == -1)
    {
        // this means that data is going be on the left subtree of bst.
        if(bst->children[0])
        {
            searchElementBST(bst->children[0],data, compare);
        }
        else {
            return NULL;
        }
    }
    else {
        return bst;
    }
    return NULL;
}


// deleting a non present data from a tree is not gonna cause an error.
void deleteElementFromBST(struct BstNode *bst, void *data, int8_t (*compare)(void *, void *), int8_t mode, void (*custom_free)(void* data))
{
    struct BstNode *toBeDeleted = searchElementBST(bst, data, compare);

    // check if the data is present in the tree.
    if (toBeDeleted) {
        // check if the node that contain the data is a leaf node .
        if (toBeDeleted->children[0] == NULL &&
            toBeDeleted->children[1] == NULL) 
        { 
            // is a leaf node, so we just delete it and set it's parent is zero.
            // if it's the left child of it's parent.
            if(toBeDeleted->parent->children[0] == toBeDeleted) toBeDeleted->parent->children[0] = NULL;
            // if it's the right child of it's parent.
            else if(toBeDeleted->parent->children[1] == toBeDeleted) toBeDeleted->parent->children[1] = NULL;
            // free the data payload of the node.
            custom_free(data);
            // free the node data structure.
            free(toBeDeleted);
        }
        else if(toBeDeleted->children[0] != NULL && toBeDeleted->children[1] == NULL)
        {
            // it's a lefty node that it has only the left child but not the right one.
            // if it's the left child of it's parent.
            if(toBeDeleted->parent->children[0] == toBeDeleted) toBeDeleted->parent->children[0] = toBeDeleted->children[0];
            // if it's the right child of it's parent.
            else if(toBeDeleted->parent->children[1] == toBeDeleted) toBeDeleted->parent->children[1] = toBeDeleted->children[1];
            
            // free the data payload of the node.
            custom_free(data);
            // free the node data structure.
            free(toBeDeleted);

        }
        else if(toBeDeleted->children[0] == NULL && toBeDeleted->children[1] != NULL)
        {
            // it's a righty node that it has only the right child but not the right one.
            // if it's the left child of it's parent.
            if(toBeDeleted->parent->children[0] == toBeDeleted) toBeDeleted->parent->children[0] = toBeDeleted->children[1];
            // if it's the right child of it's parent.
            else if(toBeDeleted->parent->children[1] == toBeDeleted) toBeDeleted->parent->children[1] = toBeDeleted->children[1];
            
            // free the data payload of the node.
            custom_free(data);
            // free the node data structure.
            free(toBeDeleted);

        }
        else if(toBeDeleted->children[0] != NULL && toBeDeleted != NULL)
        {
            // now it for sure has two subtrees, left and right.
            if(mode == 1)
            {
                // get the minimum node of the rigth subtree.
                // note: min node cannot have a left node but can have a right node.
                struct BstNode* min = findMin(toBeDeleted->children[1]);
                // if min has a right node set the parent of it the parent of min.
                // as it must be moved inpalce of toBeDeleted.
                if(min->children[1]) 
                {
                    min->parent->children[0] = min->children[1];
                    min->children[1]->parent = min->parent;
                } else {
                    // min is a leaf node, we will set the parent of min to
                    // the parent of toBeDeleted
                    min->parent->children[0] = NULL;
                    min->parent = toBeDeleted->parent;
                    // make sure that min is not a direct child of toBeDeleted.
                    if (min != toBeDeleted->children[1]) {
                        // set the children of min to the children of toBeDeleted.
                        min->children[0] = toBeDeleted->children[0];
                        min->children[1] = toBeDeleted->children[1];
                    } else {
                        min->children[0] = toBeDeleted->children[0];
                    }
                }

            }
            else if(mode == -1)
            {
                // get the maximum node of the left subtree.
                // note: max node cannot have a right node but can have a left node.
                struct BstNode* max = findMax(toBeDeleted->children[0]);
                // if max has a left node set the parent of it to the parent of max.
                // as it must be moved inpalce of toBeDeleted.
                if(max->children[0]) 
                {
                    max->parent->children[1] = max->children[0];
                    max->children[0]->parent = max->parent;
                } else {
                    // max is a leaf node, we will set the parent of max to
                    // the parent of toBeDeleted
                    max->parent->children[1] = NULL;
                    max->parent = toBeDeleted->parent;
                    // make sure that max is not a direct child of toBeDeleted.
                    if (max != toBeDeleted->children[0]) {
                        // set the children of max to the children of toBeDeleted.
                        max->children[0] = toBeDeleted->children[0];
                        max->children[1] = toBeDeleted->children[1];
                    } else {
                        max->children[1] = toBeDeleted->children[1];
                    }
                }

            }
            // free the data payload of the node.
            custom_free(data);
            // free the node data structure.
            free(toBeDeleted);
               
        }

        return ;
    }
}
struct BstNode* findMax(struct BstNode* bst)
{
    // the maximum node is the right most node in the leaf series of the bst
    // that is also a right descendant of it's parent.

    // there is no Point in finding the max node in a null bst.
    FAIL_IF_NULL(bst);
    // this flag is used to track whehter we found the max or not.
    int8_t notFound = 1;
    // this variable is gonna hold the maximum node after looping.
    struct BstNode* max = bst;
    while(notFound)
    {
        if(max->children[1])
        {
            max = max->children[1];
        }
        else {
            notFound = 0;
        }
    }
    return max;
}

struct BstNode* findMin(struct BstNode* bst)
{
    // the minimum node is the left most node in the leaf series of the bst.
    
    // there is no Point in finding the min node in a null bst.
    FAIL_IF_NULL(bst);
    // this flag is used to track whehter we found the min or not.
    int8_t notFound = 1;
    // this variable is gonna hold the minimum node after looping.
    struct BstNode* min = bst;
    while(notFound)
    {
        if(min->children[0])
        {
            min = min->children[0];
        }
        else {
            notFound = 0;
        }
    }
    return min;
}
