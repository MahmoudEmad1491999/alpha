#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void* xmalloc(size_t size);

void* xcalloc(uint32_t nmemb, size_t size);

void* xrealloc(void* ptr, size_t size);
