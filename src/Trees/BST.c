#include "BST.h"
#include "HelperFuncs.h"
#include "Macros.h"

struct BstNode *makeBSTNode(void *data) {
    struct BstNode *root = xmalloc(sizeof(struct BstNode));
    root->parent = NULL;
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void addElementToBST(struct BstNode *bst, void *data,
                     int8_t (*compare)(void *, void *)) {
    // first we need to check if the given binary search tree pointer is not
    // null.
    FAIL_IF_NULL(bst);

    // compare the given data to the data payload of bst.
    int8_t compare_result = compare(data, bst->data);

    if (compare_result == 1) {
        // if the compare result is 1, this means that the new data is going to
        // be in a node on the right subtree of bst.

        if (bst->right) // if the right child is present.
        {
            addElementToBST(bst->right, data, compare);
        } else // if the right child is not present.
        {
            struct BstNode *new_node = makeBSTNode(data);
            new_node->parent = bst;
            bst->right = new_node;
        }
    } else if (compare_result == -1) {
        // if the compare result is -1, this means that the new data is going to
        // be in a node on the left subtree of bst.

        if (bst->left) // if the left child is present.
        {
            addElementToBST(bst->left, data, compare);
        } else // if the right child is not present.
        {
            struct BstNode *new_node = makeBSTNode(data);
            new_node->parent = bst;
            bst->left = new_node;
        }
    } else {
        // this means compare result is zero and bst is actually holding data
        // payload equvilant to the given data. so return.
        return;
    }
}

struct BstNode *searchElementBST(struct BstNode *bst, void *data,
                                 int8_t (*compare)(void *data1, void *data2)) {
    // there is no meaning in searching a null binary search tree.
    // but this does not mean that we cannot return NULL.
    FAIL_IF_NULL(bst);

    int8_t compare_result = compare(data, bst->data);
    if (compare_result == 1) {
        // this means that data is going be on the right subtree of bst.
        if (bst->right) {
            // if the right subtree of bst is present, search it.
            searchElementBST(bst->right, data, compare);
        } else {
            // if the right subtree of bst is NULL this mean that the data is
            // not present.
            return NULL;
        }
    } else if (compare_result == -1) {
        // this means that data is going be on the left subtree of bst.
        if (bst->left) {
            // if the left subtree of bst is present, search it.
            searchElementBST(bst->left, data, compare);
        } else {
            // if the left subtree of bst is NULL this mean that the data is not
            // present.
            return NULL;
        }
    } else if (compare_result == 0) {
        // if compare result is zero this means that bst hold data payload
        // equivalant to given data.
        return bst;
    } else {
        FAIL("Impossible to reach!");
    }
    return NULL;
}

void deleteElementFromBST(struct BstNode *bst, void *data,
                          int8_t (*compare)(void *, void *), int8_t mode,
                          void (*custom_free)(void *data)) {
    // first: find the node that hold the data to be deleted.
    struct BstNode *toBeDeleted = searchElementBST(bst, data, compare);

    // check if the data is present in the tree.
    if (toBeDeleted) {

        // check if the node that contain the data is a leaf node .
        if (toBeDeleted->left == NULL && toBeDeleted->right == NULL) {
            // if it's the left child of it's parent, set the left child of the
            // parent to null.
            if (toBeDeleted->parent->left == toBeDeleted)
                toBeDeleted->parent->left = NULL;
            // if it's the right child of it's parent, set the right child of
            // the parent to null.
            else if (toBeDeleted->parent->right == toBeDeleted)
                toBeDeleted->parent->right = NULL;
            // free the data payload of the node.
            custom_free(toBeDeleted->data);
            // free the node data structure.
            free(toBeDeleted);
        }
        // check if it's a lefty node that it has only the left child but not
        // the right one.
        else if (toBeDeleted->left != NULL && toBeDeleted->right == NULL) {
            // check if toBeDeleted is the left child of it's parent.
            if (toBeDeleted->parent->left == toBeDeleted) {
                // the left child of toBeDeleted is going take the place of
                // toBeDeleted as the left child of toBeDeleted parent.
                toBeDeleted->parent->left = toBeDeleted->left;
                // set the parent of the left node of the toBeDeleted node to
                // the parent of the toBeDeleted.
                toBeDeleted->left->parent = toBeDeleted->parent;
            }
            // check if toBeDeleted is the right child of it's parent.
            else if (toBeDeleted->parent->right == toBeDeleted) {
                // the left child of toBeDeleted is going to take the place of
                // toBeDeleted as the right child of toBeDeleted parent.
                toBeDeleted->parent->right = toBeDeleted->left;
                // set the parent of the left node of the toBeDeleted node to
                // the parent of the toBeDeleted.
                toBeDeleted->left->parent = toBeDeleted->parent;
            }

            // free the data payload of toBeDeleted node.
            custom_free(toBeDeleted->data);
            // free the toBeDeleted data structure.
            free(toBeDeleted);

        }
        // it's a righty node that it has only the right child but not the right
        // one.
        else if (toBeDeleted->left == NULL && toBeDeleted->right != NULL) {
            // check if toBeDeleted is the left child of it's parent.
            if (toBeDeleted->parent->left == toBeDeleted) {
                // the right child of toBeDeleted is going take the place of
                // toBeDeleted as the left child of toBeDeleted parent.
                toBeDeleted->parent->left = toBeDeleted->left;
                // set the parent of the left node of the toBeDeleted node to
                // the parent of the toBeDeleted.
                toBeDeleted->left->parent = toBeDeleted->parent;
            }
            // check if toBeDeleted is the right child of it's parent.
            else if (toBeDeleted->parent->right == toBeDeleted) {
                // the right child of toBeDeleted is going to take the place of
                // toBeDeleted as the right child of toBeDeleted parent.
                toBeDeleted->parent->right = toBeDeleted->left;
                // set the parent of the left node of the toBeDeleted node to
                // the parent of the toBeDeleted.
                toBeDeleted->left->parent = toBeDeleted->parent;
            }
            // free the data payload of the toBeDeleted node.
            custom_free(toBeDeleted->data);
            // free the toBeDeleted node data structure.
            free(toBeDeleted);

        }
        // check if toBeDeleted  has both right and left child nodes.
        else if (toBeDeleted->left != NULL && toBeDeleted != NULL) {
            if (mode == 1) // mode 1 means use the mininum of the right subtree
                           // to fill in the place of the toBeDeleted node.
            {
                // get the minimum node of the rigth subtree.
                // note: min node cannot have a left node but can have a right
                // node.
                struct BstNode *min = findMin(toBeDeleted->right);

                // there is a special case that must be dealt with first, that
                // is: min is the right child of toBeDeleted.
                if (min == toBeDeleted->right) {
                    // the parent of min is going to be the parent of
                    // toBeDeleted.
                    min->parent = toBeDeleted->parent;
                    // now if the toBeDeleted is the left child of its parent,
                    // min is gonig to be so, if not min is going to be the

                    // right child of its parent.
                    (toBeDeleted->parent->left == toBeDeleted)
                        ? (toBeDeleted->parent->left = min)
                        : (toBeDeleted->parent->right = min);
                } else {
                    // min is not the right child of toBeDeleted, and of course
                    // does not have a left branch and is the left branch of
                    // it's parnet. if min has a right child, the right child is
                    // going to take it's place.
                    if (min->right) {
                        // as min is the mininum and not a child of toBeDeleted
                        // it must be the left child of it's parent.
                        min->parent->left = min->right;
                        min->right->parent = min->parent;
                    } else {
                        // if min does not have a right then it must be aleaf.
                        // setting the left branch of its parent to NULL is
                        // enough.
                        min->parent->left = NULL;
                        min->parent = toBeDeleted->parent;

                        // now if the toBeDeleted is the left child of its
                        // parent, min is gonig to be so, if not min is going to
                        // be the right child of its parent.
                        (toBeDeleted->parent->left == toBeDeleted)
                            ? (toBeDeleted->parent->left = min)
                            : (toBeDeleted->parent->right = min);
                    }
                }

            } else if (mode == -1) {
                // get the max node of the left subtree.
                // note: max node cannot have a right node but can have a left
                // node.
                struct BstNode *max = findMin(toBeDeleted->right);

                // there is a special case that must be dealt with first, that
                // is: max is the left child of toBeDeleted.
                if (max == toBeDeleted->left) {
                    // the parent of min is going to be the parent of
                    // toBeDeleted.
                    max->parent = toBeDeleted->parent;
                    // now if the toBeDeleted is the left child of its parent,
                    // max is gonig to be so, if not max is going to be the
                    // right child of its parent.
                    (toBeDeleted->parent->left == toBeDeleted)
                        ? (toBeDeleted->parent->left = max)
                        : (toBeDeleted->parent->right = max);
                } else {
                    // max is not the right child of toBeDeleted, and of course
                    // does not have a right branch and is the right branch of
                    // it's parnet. if max has a left child, the left child is
                    // going to take it's place.
                    if (max->left) {
                        // as max is the max and not a child of toBeDeleted it
                        // must be the right child of it's parent.
                        max->parent->right = max->left;
                        max->left->parent = max->parent;
                    } else {
                        // if max does not have a left then it must be a leaf.
                        // setting the right branch of its parent to NULL is
                        // enough.
                        max->parent->right = NULL;
                        max->parent = toBeDeleted->parent;

                        // now if the toBeDeleted is the left child of its
                        // parent, max is gonig to be so, if not max is going to
                        // be the right child of its parent.
                        (toBeDeleted->parent->left == toBeDeleted)
                            ? (toBeDeleted->parent->left = max)
                            : (toBeDeleted->parent->right = max);
                    }
                }
            }
            // free the data payload of the toBeDeleted node.
            custom_free(toBeDeleted->data);
            // free the node toBeDeleted data structure.
            free(toBeDeleted);
        }

        return;
    }
}
struct BstNode *findMax(struct BstNode *bst) {
    // the maximum node is the right most node in the leaf series of the bst
    // that is also a right descendant of it's parent.

    // there is no Point in finding the max node in a null bst.
    FAIL_IF_NULL(bst);
    // this flag is used to track whehter we found the max or not.
    int8_t notFound = 1;
    // this variable is gonna hold the maximum node after looping.
    struct BstNode *max = bst;
    while (notFound) {
        if (max->right) {
            max = max->right;
        } else {
            notFound = 0;
        }
    }
    return max;
}

struct BstNode *findMin(struct BstNode *bst) {
    // the minimum node is the left most node in the leaf series of the bst.

    // there is no Point in finding the min node in a null bst.
    FAIL_IF_NULL(bst);
    // this flag is used to track whehter we found the min or not.
    int8_t notFound = 1;
    // this variable is gonna hold the minimum node after looping.
    struct BstNode *min = bst;
    while (notFound) {
        if (min->left) {
            min = min->left;
        } else {
            notFound = 0;
        }
    }
    return min;
}
