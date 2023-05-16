#include <stdio.h>
#include "HelperFuncs.h"
#include "Array.h"

int main(int argc, char** argv)
{
    struct Array* array = makeArray(2,NULL);
    int* x = malloc(sizeof(int)), *y = malloc(sizeof(int));
    *x = 100; *y = 200;
    printf("%p\n", array->first);
    printf("%u\n", array->size);
    ArrayAtSet(array, 0, x); 
    ArrayAtSet(array, 1, y); 

    printf("%d\n", *((int*) (array->first[0])));

    printf("%d\n", *((int*) (ArrayAtGet(array, 0))));
    freeArray(array);

}
