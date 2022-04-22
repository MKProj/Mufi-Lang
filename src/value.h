#ifndef mufi_value_h
#define mufi_value_h

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value* values;
}ValueArray;

//> Creates a new empty value array
void initValueArray(ValueArray* array);
//> Appends to the end of a value array
void writeValueArray(ValueArray* array, Value value);
//> Frees the memory of a value array
void freeValueArray(ValueArray* array);
//> Prints a value
void printValue(Value value);
#endif
