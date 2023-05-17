#ifndef BST_H
#define BST_H
#include <stdint.h>
#include "Queue.h"

/**
 * Purpose: this sturcture is used to represent a binary search tree
 *          node.
 * @children    is an array of 2 pointer to bstNodes the left and the right.
 * @data        is the data payload of the node.
 * @parent      is the parent of the node.
 * */
struct BstNode {
    struct BstNode *left;
    struct BstNode *right;
    void *data;
    struct BstNode *parent;
};

/**
 * Purpose: this function is used to make a binary search tree.
 * @data    the data payload of the root node.
 * @return  return the root of the to be created binary search tree.
 */
struct BstNode *makeBST(void *data);

/**
 * Purpose: this function is used to free the whole datastructure and the data associated with,
 *          each node.
 * @root    is pointer to the root of the binary search tree.
 */
void freeBst(struct BstNode* root, void (*custom_free)(void* data));

/**
 * Purpose: this function is used to add an element to a binary search tree.
 * @root    binary search tree to operate on.
 * @data    pointer to the data element.
 * @compare this is function pointer to compare the data payload of different
 * nodes.
 *          characteristic of the compare function.
 *          1 means data1 > data2
 *          0 means data1 = data2
 *          -1 means data1 < data2
 */
void addElementToBST(struct BstNode *root, void *data,
                     int8_t (*compare)(void *data1, void *data2));

/**
 * Purpose: this function is used to search for an element on the binary
 *          search tree.
 * @bst     the binary search tree to search at.
 * @data    the data element to search.
 * @return  pointer to the node that hold the searched data item.
 *          characteristic of the compare function.
 *          +1  means data1 > data2
 *          0  means data1 = data2
 *          -1 means data1 < data2
 * */
struct BstNode *searchElementBST(struct BstNode *bst, void *data,
                                 int8_t (*compare)(void *data1, void *data2));

/**
 * Pupose:  this function is used to delete an element from the binary
 *          search tree.
 * @bst     the binary tree in question.
 * @data    pointer to the data element to be removed.
 * @compare this is function pointer to compare the data payload of different
 * nodes.
 *          characteristic of the compare function.
 *          +1  means data1 > data2
 *          0  means data1 = data2
 *          -1 means data1 < data2
 */
void deleteElementFromBST(struct BstNode *bst, void *data,
                          int8_t (*compare)(void *data1, void *data2),
                          int8_t mode, void (*custom_free)(void *data));
/**
 * Purpose: this function is used to find the maximum node of a binary search
 * tree
 * @bst     is the binary search tree to be searched.
 */
struct BstNode *findMax(struct BstNode *bst);
/**
 * Purpose: this function is used to find the minimum node of a binary search
 * tree
 * @bst     is the binary search tree to be searched.
 */
struct BstNode *findMin(struct BstNode *bst);
#endif
