#include <stdlib.h>
#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize){
    // If the new size is 0, we free the array
    if (newSize == 0){
        free(pointer);
        return NULL;
    }
    // use realloc to handle any grow, shrink, etc.
    void* result = realloc(pointer, newSize);
    // if allocation fails exit program
    if (result == NULL) exit(1);
    // return the result of the reallocation
    return result;
}