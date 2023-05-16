#ifndef TREE_H
#define TREE_H
#include <stdint.h>

// depth:   is how many edges till the root.
// height:  is how many edges till the furthest leaf.

/**
 * Purpose: this structure represent the generic tree data strucutre. 
 * @children    is an array of pointers to sub trees.
 * @data        pointer to the data payload of the node. 
 * @parent      is the parent node of this node.
 *              recording it is very helpful for certian applications.
 * @degree      is the maximum possible number of children of the node.
 *              i.e. the length of the children array
 **/
struct TreeNode {
    struct TreeNode** children;
    struct TreeNode* parent;
    void* data;
    uint32_t degree;
};

// when constructing a node what is the kind of information we need to store.
// the data payload first of all the dat payload must be dynamically allocated before given to the creating function.
// this is not a specific rule for this datastructure only but for all the data strcutures in this library.

/**
 * Purpose: this function is used to create  a tree node,
 * @parent  the parent of the to be created node.
 * @data    pointer to the data payload.
 * @degree  the maximum number of children this node can have.
 * @return  pointer to the node that it getting created.
 **/
struct TreeNode* makeTreeNode(struct TreeNode* parent, void* data, uint32_t degree );



/**
 * Purpose: this function is used to free the whole tree with datapayload using custom_free.
 * @root    the root node of the tree structure that we want to free.
 * @custome_free    the custom freeing function for the datapayload.
 *
 */
void freeTree(struct TreeNode* treeNode, void(*custom_free)(void* data));

/**
 * Purpose: traverse the given tree iteratively by level.
 * @root        the root node of the tree.
 * @hook        is the function that gets called with the node.
 * */
void BreadthTraverse(struct TreeNode* root, void (*hook)(struct TreeNode* data) );

/**
 * Purpose: traverse the given tree iteratively by depth in an preorder way.
 * @root        the root node of the tree.
 * @hook        is the function that gets called with the node.
 * */
void PreOrderTraverse(struct TreeNode* root, void (*hook)(struct TreeNode* data) );

/**
 * Purpose: traverse the given tree iteratively by depth in an inorder way.
 * @root        the root node of the tree.
 * @hook        is the function that gets called with the node.
 * */
void InOrderTraverse(struct TreeNode* root, void (*hook)(struct TreeNode* data) );

/**
 * Purpose: traverse the given tree iteratively by depth in a postorder way.
 * @root        the root node of the tree.
 * @hook        is the function that gets called with the node.
 * */
void PostOrderTraverse(struct TreeNode* root, void (*hook)(struct TreeNode* data) );
#endif

