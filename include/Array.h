#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>
#include <stdint.h>

/**
 * this is dynamic array data structure.
 */
struct Array {
    void** first;                /* pointer to the first element address. */
    uint32_t size;               /* the capacity of the array. */
    void (*custom_free)(void *); /* function pointer to a free function that gets called
                                    when the element to be freed. */
};

/**
 * this function is used to make a new array instances.
 * @size     the initial capacity of the array.
 * @custom_free        the hook that gets called before getting freed for each element pointer.
 * if hook is null just the free function is going get called.
 */
struct Array *makeArray(uint32_t size, void (*custom_free)(void *));

/** this function gets called to free the array datastructure with each individual element.
 * @array       the array pointer to get freed.
 */

void freeArray(struct Array *array);


/**
 * this function is used as array subscript operator but only on the rhs.
 * @array the array to work on. 
 * @index the index at which we want to work on.
 *  
 * if index is out of scope the array is going to expand untill it fits,
 * and is going to return null as there is not element present at the specified index..
 *
 * @return the pointer to the element stored.
 */
void const* ArrayAtGet(struct Array *array, uint32_t index);

/*
 * this function is used as array subscript operator but only as the lhs.
 * @array the array to work on. 
 * @index the index at which we want to work on.
 *  
 * if index is out of scope the array is going to expand untill it fits.
 * */
void ArrayAtSet(struct Array* array, uint32_t index, void* new_element);
#endif
