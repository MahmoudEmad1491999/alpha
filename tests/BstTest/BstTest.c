#include "Bst.h"
#include <stdio.h>
#include <stdlib.h>
#include "HelperFuncs.h"
int8_t c_int(void* data1, void* data2)
{
    if(*(int*)data1 == *(int*)data2)
    {
        return 0;
    }
    else if(*(int*)data1 > *(int*)data2)
    {
        return 1;
    }
    else {
        return -1;
    }
}

void printint(void* data)
{
    printf("%d \n", *(int*)data);
}
int main(int argc, char** argv)
{
    int *a = xmalloc(sizeof(int)), *b = xmalloc(sizeof(int)),
        *c = xmalloc(sizeof(int)), *d = xmalloc(sizeof(int)),
        *e = xmalloc(sizeof(int)), *f = xmalloc(sizeof(int)),
        *g = xmalloc(sizeof(int)), *h = xmalloc(sizeof(int));

    *a = 100;
    *b = 200;
    *c = 150;
    *d = 43;
    *e = 45;
    *f = 145;
    *g = 1000;
    *h = 3;

    struct BstNode* bst = makeBST(e);
    addElementToBST(bst, b,(int8_t (*)(void*, void*))c_int);
    addElementToBST(bst, d,(int8_t (*)(void*, void*))c_int);
    addElementToBST(bst, a,(int8_t (*)(void*, void*))c_int);
    addElementToBST(bst, h,(int8_t (*)(void*, void*))c_int);
    addElementToBST(bst, f,(int8_t (*)(void*, void*))c_int);
    addElementToBST(bst, g,(int8_t (*)(void*, void*))c_int);
    addElementToBST(bst, c,(int8_t (*)(void*, void*))c_int);
    freeBst(bst, free); 
    return 0;
}
