//> Frontend of mufi
#ifndef mufi_vm_h
#define mufi_vm_h

#include "chunk.h"
#include "value.h"
#include "object.h"

#define STACK_MAX 256

//> The runtime virtual machine
typedef struct {
    Chunk* chunk; // Contains a dynamic array of chunks
    uint8_t* ip; // Instruction pointer
    Value stack[STACK_MAX]; // The virtual machine's stack
    Value* stackTop; // Top of the stack, always point to where the next item should be pushed
    Obj* objects; // Head of the object linked list
}VM;
//> Error result of virtual machine's interpretation
typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
}InterpretResult;

// Global vm variable
extern VM vm;

//> Initializes the VM
void initVM();
//> Deallocates the VM's resources
void freeVM();
//> Interprets and runs the code
InterpretResult interpret(const char* source);
//> Pushes a value to the stack
void push(Value value);
//> Pops a value off the stack
Value pop();

#endif
