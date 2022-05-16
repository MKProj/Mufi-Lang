#include <stdlib.h>
#include "memory.h"
#include "vm.h"

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

static void freeObject(Obj* object) {
    switch (object->type) {
        case OBJ_CLOSURE:{
            FREE(ObjClosure, object);
            break;
        }
        case OBJ_FUNCTION: {
            ObjFunction* function = (ObjFunction*)object;
            freeChunk(&function->chunk);
            FREE(ObjFunction, object);
            break;
        }
        case OBJ_NATIVE:
            FREE(ObjNative, object);
            break;
        case OBJ_STRING: {
            ObjString* string = (ObjString*)object;
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, object);
            break;
        }
    }
}

void freeObjects(){
    Obj* object = vm.objects;
    while (object != NULL){
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }
}