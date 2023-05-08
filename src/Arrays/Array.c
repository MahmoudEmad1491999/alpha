#include "Array.h"
#include "HelperFuncs.h"
#include "Macros.h"
#include <stdlib.h>

DirectArray *makeDirectArray(uint32_t len, uint32_t element_size,
                       void (*hook)(void *)) {
    DirectArray *array = xmalloc(sizeof(DirectArray));
    array->head = xcalloc(len > 0 ? len : 10, element_size);
    array->len = len > 0 ? len : 10;
    FAIL_IF_ZERO(element_size);
    array->element_size = element_size;
    array->hook = hook;
    return array;
}

void freeDirectArray(DirectArray *array) {
    if (array) {
        if(array->hook)
        {
            for (uint32_t index = 0; index < array->len; index++) {
                array->hook(array->head + index * array->element_size);
            }
        }
        free(array->head);
        free(array);
    }
}

void *DirectArrayAt(DirectArray *array, uint32_t index) {
    FAIL_IF_NULL(array);
    FAIL_IF_GREATER_OR_EQUAL(index, array->len);
    return array->head + index * array->element_size;
}


IndirectArray* makeIndirectArray(uint32_t len, uint32_t element_size, void (*freeElement)(void*))
{
    IndirectArray* array = xmalloc(sizeof(IndirectArray));
    array->head = xcalloc(len > 0 ? len : 10, sizeof(void*));
    array->len = len > 0 ? len : 10;
    FAIL_IF_ZERO(element_size);
    array->element_size = element_size;
    array->freeElement = freeElement ? freeElement: free;
    return array;
}

void freeIndirectArray(IndirectArray* array)
{
    if(array)
    {
        for(int index = 0; index < array->len; index++)
        {
            array->freeElement(*(array->head+index));
        }
        free(array->head);
        free(array);
    }
}

void** IndirectArrayAt(IndirectArray* array, uint32_t index)
{
    FAIL_IF_NULL(array);
    FAIL_IF_GREATER_OR_EQUAL(index, array->len);

    return array->head + index;
}
