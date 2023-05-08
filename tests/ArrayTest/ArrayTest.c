#include <stdio.h>
#include "HelperFuncs.h"
#include "Array.h"

int main(int argc, char** argv)
{
    /*
    DirectArray* array = makeDirectArray(10,sizeof(int32_t), NULL);
    *( (int32_t*)DirectArrayAt(array, 0)) = 100;
    printf("%d\n", *((int32_t*)DirectArrayAt(array, 0)));
    freeDirectArray(array);
     */
    

    IndirectArray* array = makeIndirectArray(10, sizeof(int32_t),NULL);
    int32_t* t = xmalloc(sizeof(int32_t));
    *t = 100;
    *((int32_t**)IndirectArrayAt(array, 0)) = t;
    
    printf("%d\n", *(*((int32_t**)(IndirectArrayAt(array,0)))));
    freeIndirectArray(array);
    printf("Hello there\n");
    return 0;
}
