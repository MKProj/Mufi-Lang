#include <stdio.h>
#include "value.h"
#include "memory.h"

// Creates a new empty array
void initValueArray(ValueArray* array){
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

// Appends to the end of a value array
void writeValueArray(ValueArray* array, Value value){
    // Checks if array is full
    if (array->capacity < array->count + 1){
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }
    // Append to the array
    array->values[array->count] = value;
    array->count++;
}

// Deallocates the value array and creates an empty one
void freeValueArray(ValueArray* array){
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

// Prints a value
void printValue(Value value){
    printf("%g", value);
}