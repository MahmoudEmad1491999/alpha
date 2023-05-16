#include "Array.h"
#include "HelperFuncs.h"
#include "Macros.h"
#include <stdlib.h>

struct Array *makeArray(uint32_t size, void (*custom_free)(void *)) {
    struct Array *array = xmalloc(sizeof(struct Array));
    // if len is zero, first is going be NULL.
    array->first = xcalloc(size, sizeof(void*));
    array->size = size;
    array->custom_free = custom_free ? custom_free : free;

    return array;
}

void freeArray(struct Array *array) {
    if(array) {
        for (uint32_t index = 0; index < array->size; index++) {
            if(array->first[index])
            {
                // free individual elements if present.
                array->custom_free(array->first[index]);
            }
        }
       
        // free the array of pointers.
        free(array->first);

        // free the whole structure.
        free(array);
    }
}

void const* ArrayAtGet(struct Array *array, uint32_t index) {
    FAIL_IF_NULL(array);
    // if index is in bound.
    if(index < array->size)
    {
        return array->first[index];
    }
    else {
        // if index is out of bound.
        if(array->size)
        {
            // size is not null so the new size can be calcualted by new_size = old_size * resizing factor ;
            // resizing factor = ((index+1) / old size)+ 1;
            array->first = xrealloc(array->first, sizeof(void*) * array->size * (((index+1)/array->size) + 1));
            array->size = array->size * ((index+1)/array->size) + 1;
        }
        else 
        {
            // size is zero so new size = index + 1; and that element is going be the last.
            array->first = xcalloc(index+1 , sizeof(void*) );
            array->size = index+1;
        }
        return NULL;
    }
}

void ArrayAtSet(struct Array *array, uint32_t index, void *new_element)
{
    // element is in bound.
    if(index < array->size)
    {
        // if the old element is not null we free it first.
        if(array->first[index])
        {
            array->custom_free(array->first[index]);

        }
        // then we set that index to the new element.
            array->first[index] = new_element;
    }
    else 
    {
        // if index is out of bound.
        if(array->size)
        {
            // size is not zero. we resize.
            // the new size = old size * resize_factor.
            // resize_factor = ((index + 1) / old_size) + 1
            array->first = xrealloc(array->first, sizeof(void*) * array->size * ((index+1)/array->size + 1));
            array->size = array->size * ((index+1)/array->size) + 1;
        }
        else 
        {
            // size is zero, then new_size = index + 1.
            array->first = xcalloc(index+1 , sizeof(void*) );
            array->size = index+1;
        }
        // after resizing we set that index to the new element.
        array->first[index] = new_element;
    }
}

