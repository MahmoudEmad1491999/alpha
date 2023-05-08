#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "HelperFuncs.h"
#include "Macros.h"

int main(int argc, char**argv)
{
    struct SLList* list = makeSLList(NULL);
    int* x = malloc(sizeof(int));
    *x = 100;
    int* y = malloc(sizeof(int));
    *y = 200;

    SLListAppend(list, x);
    SLListPrepend(list, y);

    printf("%d\n", x == y);
    freeSLList(list);
    return 0;
}
