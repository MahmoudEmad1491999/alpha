#ifndef BST_H
#define BST_H
#include "Tree.h"

/**
 * Purpose: this function is used to make a binary search tree.
 * @data    the data payload of the root node.
 * @return  return the root of the to be created binary search tree.
 */
struct TreeNode *makeBST(void *data);

/**
 * Purpose: this function is used to add an element to a binary search tree.
 * @bst     binary search tree to operate on.
 * @data    pointer to the data element.
 * @compare this is function pointer to compare the data payload of different
 * nodes.
 */
void addElementToBST(struct TreeNode *bst, void *data,
                     int8_t (*compare)(void *data1, void *data2));

/**
 * Purpose: this function is used to search for an element on the binary
 *          search tree.
 * @bst     the binary search tree to search at.
 * @data    the data element to search.
 * @return  pointer to the node that hold the searched data item.
 * */
struct TreeNode* searchElementBST(struct TreeNode *bst, void *data,
                        int8_t (*compare)(void *data1, void *data2));

/**
 * Pupose:  this function is used to delete an element from the binary
 *          search tree.
 * @bst     the binary tree in question.
 * @data    pointer to the data element to be removed.
 * @compare this is function pointer to compare the data payload of different
 * nodes.
 */
void deleteElementFromBST(struct TreeNode *bst, void *data,
                          int8_t (*compare)(void *data1, void *data2));
/**
 * Purpose: this function is used to find the maximum node of a binary search tree
 * @bst     is the binary search tree to be searched.
 */
struct TreeNode* findMax(struct TreeNode* bst);
/**
 * Purpose: this function is used to find the minimum node of a binary search tree
 * @bst     is the binary search tree to be searched.
 */
struct TreeNode* findMin(struct TreeNode* bst);
#endif
