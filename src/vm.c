#include <stdarg.h>
#include <stdio.h>
#include "common.h"
#include "compiler.h"
#include "vm.h"
#include "debug.h"

// Global vm
VM vm;
// Resets the stack
static void resetStack(){
    vm.stackTop = vm.stack;
}

// returns runtime errors
static void runtimeError(const char* format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[instruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
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

static Value peek(int distance){
    return vm.stackTop[-1-distance];
}

static bool isFalsey(Value value){
    return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

// runs the virtual machine
static InterpretResult run(){
#define READ_BYTE() (*vm.ip++) // Reads each instruction
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
  do {                \
       if (IS_INT(peek(0)) && IS_INT(peek(1))){                                                \
            int b = AS_INT(pop());         \
            int a = AS_INT(pop());                                                             \
            push(INT_VAL(a op b));      \
       } else if (IS_DOUBLE(peek(0)) && IS_DOUBLE(peek(1))) {                                  \
            double b = AS_DOUBLE(pop());         \
            double a = AS_DOUBLE(pop());                                                             \
            push(DOUBLE_VAL(a op b));      \
       }  else if (IS_BOOL(peek(0)) && IS_BOOL(peek(1))){                                      \
            bool b = AS_BOOL(pop());                                                         \
            bool a = AS_BOOL(pop());                                                            \
           push(BOOL_VAL(a op b));\
       }        \
       else {   \
              runtimeError("Operands must be either both integer or both double numbers.");                \
               return INTERPRET_RUNTIME_ERROR;       \
       }              \
       }while(false)
#define BINARY_OP_COMPARISON(op) \
      do{                           \
      bool b = AS_BOOL(pop());   \
      bool a = AS_BOOL(pop());   \
      push(BOOL_VAL(a op b));\
} while(false)
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
            case OP_NIL: push(NIL_VAL); break;
            case OP_TRUE: push(BOOL_VAL(true)); break;
            case OP_FALSE: push(BOOL_VAL(false)); break;
            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_GREATER:
                BINARY_OP_COMPARISON(>); break;
            case OP_LESS:
                BINARY_OP_COMPARISON(<); break;
            case OP_ADD: BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE: BINARY_OP(/); break;
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_NEGATE:
                if (!IS_INT(peek(0)) || !IS_DOUBLE(peek(0))){
                    runtimeError("Operand must be a number (int/double).");
                    return INTERPRET_RUNTIME_ERROR;
                }
                if (IS_INT(peek(0))){
                    push(INT_VAL(-AS_INT(pop())));
                } else {
                    push(DOUBLE_VAL(-AS_DOUBLE(pop())));
                }
                break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
#undef BINARY_OP_COMPARISON
}

// Interprets the chunks
InterpretResult interpret(const char* source){
    Chunk chunk;
    initChunk(&chunk);
    if(!compile(source, &chunk)){
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();
    freeChunk(&chunk);
    return result;
}