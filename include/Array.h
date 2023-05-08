#include <stddef.h>
#include <stdint.h>
typedef struct {
    void *head;
    uint32_t len;
    uint32_t element_size;
    void (*hook)(void *);

} DirectArray;

DirectArray *makeDirectArray(uint32_t len, uint32_t element_size,
                       void (*hook)(void *));

void freeDirectArray(DirectArray *directArray);

void *DirectArrayAt(DirectArray *directArray, uint32_t index);

typedef struct {
    void **head;
    uint32_t len;
    uint32_t element_size;
    void (*freeElement)(void *);
} IndirectArray;

IndirectArray* makeIndirectArray(uint32_t len, uint32_t element_size, void (*freeElement)(void*));

void freeIndirectArray(IndirectArray* indirectArray);

void** IndirectArrayAt(IndirectArray* indirectArray, uint32_t index);

