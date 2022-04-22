//> Manages memory allocation in mufi 
#ifndef mufi_memory_h 
#define mufi_memory_h 

#include "common.h"

// To grow capacity we check if the capacity is less than 8,
// if so, we make it 8, if not we multiply the old capacity by 2.
//> Grows the capacity of dynamic arrays
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8: (capacity) * 2)

// Knowing what the new capacity is, we can also grow an array to the same capacity
//> Grows the array with a desired capacity
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
        (type*)reallocate(pointer, sizeof(type) * oldCount, \
        sizeof(type) * (newCount))

//> Frees a dynamic array
#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type)*(oldCount), 0) \

//> Used to reallocate memory for arrays
void* reallocate(void* pointer, size_t oldSize, size_t newSize);
#endif