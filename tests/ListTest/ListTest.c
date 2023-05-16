#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "HelperFuncs.h"
#include "Macros.h"

int main(int argc, char**argv)
{
    int* x = malloc(sizeof(int));
    *x = 100;
    int* y = malloc(sizeof(int));
    *y = 200;
    int* z = malloc(sizeof(int));
    *z = 300;
    struct SLList* list = makeSLList(free);
    printf("%d\n", list->len);

    SLListAppend(list, x);

    
    printf("%d\n", list->len);

    SLListPrepend(list, y);

    printf("%d\n", list->len);

    SLListInsert(list,z, 1);

    printf("%d\n", list->len);

    printf("%d, %d, %d\n", *(int *)(SLListAtGet(list, 0)),
           *(int *)(SLListAtGet(list, 1)), *(int *)(SLListAtGet(list, 2)));


    SLListDelete(list, 1, NULL);

    printf("%d\n", list->len);
    printf("%d, %d\n", *(int *)(SLListAtGet(list, 0)),
           *(int *)(SLListAtGet(list, 1)));
    freeSLList(list);
    return 0;
}
