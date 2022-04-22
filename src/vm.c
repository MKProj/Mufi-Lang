#include <stdio.h>
#include "common.h"
#include "vm.h"
#include "debug.h"


VM vm;

static void resetStack(){
    vm.stackTop = vm.stack;
}

// Initializes the virtual machine
void initVM(){
    resetStack();
}

// Frees the virtual machine
void freeVM(){

}

// Pops value off of the stack
void push(Value value){
    *vm.stackTop = value; //Puts value on the top of the stack
    vm.stackTop++; // Increment the stack top
}

Value pop(){
    vm.stackTop--; // Goes to the top value on the stack
    return *vm.stackTop; // Returns the value
}

// runs the virtual machine
static InterpretResult run(){
#define READ_BYTE() (*vm.ip++) // Reads each instruction
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#ifdef  DEBUG_TRACE_EXECUTION
    printf("         ");
    for(Value* slot = vm.stack; slot < vm.stackTop; slot++){
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    for(;;){
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_NEGATE:
                push(-pop()); break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
}

// Interprets the chunks
InterpretResult interpret(Chunk* chunk){
    vm.chunk = chunk;
    vm.ip = chunk->code;
    return run();
}