#include "Tree.h"
#include "HelperFuncs.h"



int main(int argc, char* argv[])
{

    int* x, *y, *z;
    x = xmalloc(sizeof(int));
    y = xmalloc(sizeof(int));
    z = xmalloc(sizeof(int));

    struct TreeNode* root = makeTreeNode(NULL,x, 2);
    struct TreeNode* left = makeTreeNode(root,y, 2);
    struct TreeNode* right = makeTreeNode(root,z, 2);
    root->children[0] = left;
    root->children[1] = right;

    freeTree(root, free);
    return 0;

}
