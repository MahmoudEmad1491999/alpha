#include "Tree.h"
#include "BST.h"
#include "HelperFuncs.h"
#include "Macros.h"

struct TreeNode* makeBST(void* data)
{
    struct TreeNode* bst = makeTreeNode(NULL, data, 2);
    return bst;
}

void addElementToBST(struct TreeNode *bst, void *data, int8_t (*compare)(void *, void *))
{
    // first we need to check if the given binary search tree pointer is not null.
    FAIL_IF_NULL(bst);
    // create a new node with the parent set to NULL temporarily.
    struct TreeNode* newNode = makeTreeNode(NULL, data, 2);
    // found flag is zero until we find the position to insert the new node.
    int8_t notFound = 1;
    // we will use the bst as a current node when searching for the position to insert to.
    while(notFound)
    {
        // compare the data payload of to be added node with the current node, i.e. bst.
        if(compare(data,bst->data) > 0)    
        { // if the comparision result is bigger than 0 this mean the new node will be in
          // in the right subtree of the current node.
            
            if(bst->children[1] != NULL) {
                // if the current right subtree is not null,
                // this mean we have to search it, and the not found is still 1.
                bst = bst->children[1];
                notFound = 1;
            }
            else
            {
                // if the current right subtree is NULL basically set current 
                // right subtree to the new node and the new node parent to current.
                // and set not found = 0 to stop looping.
                newNode->parent = bst;
                bst->children[1] = newNode;
                notFound = 0;        
            }
        }
        else if(compare(data,bst->data) < 0)    
        { 
            // if the comparision result is less than 0 this mean the new node will be in
            // in the left subtree of the current node.
            if(bst->children[0] != NULL) {
                // if the current left subtree is not null,
                // this mean we have to search it, and the not found is still 1.
                bst = bst->children[0];
                notFound = 1;
            }
            else
            {
                // if the current right subtree is NULL basically set current 
                // left subtree to the new node and the new node parent to current.
                // and set not found = 0 to stop looping.
                newNode->parent = bst;
                bst->children[0] = newNode;
                notFound = 0;        
            }
        }
    }
}

struct TreeNode* searchElementBST(struct TreeNode *bst, void *data, int8_t (*compare)(void* data1, void* data2))
{
    // there is no meaning in searching a null binary search tree.
    FAIL_IF_NULL(bst);
    
    // we are going to use bst as a current node indicator,
    // instead of just the head of the binary tree.
    // this variable is used to track the searched item found or not.
    int8_t notFound = 1;
    // loop until you find or have a dead end.
    while(notFound)
    {
        // compare the data with the current node if it's greater than 0,
        // then that mean that the searched node is not in the left sub tree.
        // and mean that the searched data may be in the right sub tree.
        if(compare( data, bst->data) > 0)
        {
            // if the right sub tree is not null set current to it and loop againe.
            if(bst->children[1] != NULL)
            {
                bst = bst->children[0];
                notFound = 1;
            }
            // if the right sub tree is NULL return NULL.
            else 
            {
                return NULL;
            }
        }
        // if the data is less than the data at current,
        // then the data element is not in the right subtree, and may be
        // in the left subtree
        else if(compare(data, bst->data) < 0)
        {
            // if the left subtree is not null search it by looping againe, and setting 
            // current to the left subtree.
            if(bst->children[0] != NULL)
            {
                bst = bst->children[0];
                notFound = 1;
            }
            // if the left subtree is NULL return NULL as the element is not found.
            else
            {
                return NULL;
            }
        }
        // if the data is not less than the data of current,
        // and the data is not greater than current,
        // then it must be equal.
        else
        {
            // set not found to 0 as it is the current node that match the given data.
            notFound = 0;
        }
    }
    return bst;
}


// deleting a non present data from a tree is not gonna cause an error.
void deleteElementFromBST(struct TreeNode *bst, void *data, int8_t (*compare)(void *, void *))
{
    // there is no point of performing a delete operation on a null DS.
    FAIL_IF_NULL(bst);
    
    // this flag represent the state of searching for the to be deleted node.
    int8_t notFound = 1;
    // this pointer is gonna point to the node that hold the data to be deleted,
    // or null if it's not found.
    struct TreeNode* toBeDeleted = NULL;
   
    // loop until you find the node or reach a dead end.
    // we are gonna use @bst as a current node indicator instead of the head of the bst.
    while(notFound)
    {
        // compare the data payload of both the given data and current node.
        // if it's >0 this means if the deleted node is present, it's gonna be
        // in the right subtree.
        if(compare( data, bst->data) > 0)
        {
            // if the right subtree is null this mean the to be deleted node is not 
            // present in the tree, so break and return.
            if (bst->children[1] == NULL)
            {
                toBeDeleted = NULL;
                break;
            }
            else
            {
                // if the right subtree is not null set current to it and set not found to 1
                // so that it can loop and retest.
                bst = bst->children[1];
                notFound = 1;
            }
        }
        // if it's <0 this means if the deleted node is present, it's gonna be
        // in the left subtree.
        else if(compare(data, bst->data) < 0)
        {
            // if the left subtree is null this means that the to be deleted node is not
            // in the tree as a whole so break and return. 
            if(bst->children[0] != NULL)
            {
                toBeDeleted = NULL;
                break;
            }
            else
            {
                // if the left subtree is not null set current to it and notfound = 1 so
                // it can loop and retest.
                bst = bst->children[0];
                notFound = 1;
            }
        }
        // if the data payload of the to be deleted node is equal to current then
        // current is the toBeDeleted Node.
        else
        {
            // set notFound = 0 so the looping stops.
            notFound = 0;
            // set the to be deleted node to the current "bst".
            toBeDeleted = bst;
        }
    }

    // after looping the to be deleted node is gonna be either NULL or pointing the the to be deleted
    // node.
    if(toBeDeleted)
    {
        // if the toBeDeleted has no children.
        if(toBeDeleted->children[0] == NULL && toBeDeleted->children[1] == NULL)
        {
            free(toBeDeleted->data);
            free(toBeDeleted->children);
            free(toBeDeleted);
        }
        // if the toBeDeleted has one right subtree.
        else if(toBeDeleted->children[1] != NULL)
        {
            struct TreeNode* temp = toBeDeleted->children[1];
            temp->parent = toBeDeleted->parent;
            // if the toBeDeleted node is the left child of it's parent then,
            // the right subtree of the toBeDeleted is going to be the left subtree of it's parent.
            if(toBeDeleted == toBeDeleted->parent->children[0])
            {
                toBeDeleted->parent->children[0] = temp;
            }
            // if the toBeDeleted node is the right child of it's parent then,
            // the right subtree of the toBeDeleted is going to be the right subtree of it's parent.
            else 
            {
                toBeDeleted->parent->children[1] = temp;
            }

            free(toBeDeleted->data);
            free(toBeDeleted->children);
            free(toBeDeleted);
        }
        // if the toBeDeleted has one left subtree.
        else if(toBeDeleted->children[0] != NULL)
        {
            struct TreeNode* temp = toBeDeleted->children[0];
            temp->parent = toBeDeleted->parent;
            // if the toBeDeleted node is the left child of it's parent then,
            // the right subtree of the toBeDeleted is going to be the left subtree of it's parent.
            if(toBeDeleted == toBeDeleted->parent->children[0])
            {
                toBeDeleted->parent->children[0] = temp;
            }
            // if the toBeDeleted node is the right child of it's parent then,
            // the right subtree of the toBeDeleted is going to be the right subtree of it's parent.
            else 
            {
                toBeDeleted->parent->children[1] = temp;
            }

            free(toBeDeleted->data);
            free(toBeDeleted->children);
            free(toBeDeleted);
        }
        // if the toBeDeleted has both subtrees.
        else
        {
            // find the minimum node in the right subtree.
            struct TreeNode* temp = findMin(toBeDeleted->children[1]);
            // set the parent of the mininum node to the parent of the toBeDeleted
            // node.
            temp->parent = toBeDeleted->parent;
            if(toBeDeleted == toBeDeleted->parent->children[0])
            {
                toBeDeleted->parent->children[0] = temp;
            }
            else 
            {
                toBeDeleted->parent->children[1] = temp;
            }
            temp->children[0] = toBeDeleted->children[0];
            temp->children[1] = toBeDeleted->children[1];

            free(toBeDeleted->data);
            free(toBeDeleted->children);
            free(toBeDeleted);
        }
    }
}


struct TreeNode* findMax(struct TreeNode* bst)
{
    // the maximum node is the right most node in the leaf series of the bst.
    
    // there is no Point in finding the max node in a null bst.
    FAIL_IF_NULL(bst);
    // this flag is used to track whehter we found the max or not.
    int8_t notFound = 1;
    // this variable is gonna hold the maximum node after looping.
    struct TreeNode* max = bst;
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

struct TreeNode* findMin(struct TreeNode* bst)
{
    // the minimum node is the left most node in the leaf series of the bst.
    
    // there is no Point in finding the min node in a null bst.
    FAIL_IF_NULL(bst);
    // this flag is used to track whehter we found the min or not.
    int8_t notFound = 1;
    // this variable is gonna hold the minimum node after looping.
    struct TreeNode* min = bst;
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
