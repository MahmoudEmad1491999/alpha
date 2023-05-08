#include "HelperFuncs.h"

void* xmalloc(size_t size)
{
    void* x = malloc(size);
    if(!x) 
    {
        fprintf(stderr, "malloc failed!");
        exit(-1);
    }
    return x;
}

void* xcalloc(uint32_t nmemb, size_t size)
{
    void* x = calloc(nmemb, size);
    if(!x)
    {
        fprintf(stderr, "calloc failed!");
        exit(-1);
    }
    return x;
}


void* xrealloc(void* ptr, size_t size)
{
    void* x = realloc(ptr, size);
    if(!x)
    {
        fprintf(stderr, "calloc failed!");
        exit(-1);
    }
    return x;
}
