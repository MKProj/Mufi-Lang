#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "compiler.h"
#include "vm.h"
#include "debug.h"
#include "memory.h"
#include "object.h"
#include "stdlib/stdlib.h"

// Global vm
VM vm;

// Resets the stack
static void resetStack(){
    vm.stackTop = vm.stack;
    vm.frameCount = 0;
}

// returns runtime errors
static void runtimeError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    for (int i = vm.frameCount - 1; i >= 0; i--) {
        CallFrame* frame = &vm.frames[i];
        ObjFunction* function = frame->function;
        size_t instruction = frame->ip - function->chunk.code - 1;
        fprintf(stderr, "[line %d] in ", // [minus]
                function->chunk.lines[instruction]);
        if (function->name == NULL) {
            fprintf(stderr, "script\n");
        } else {
            fprintf(stderr, "%s()\n", function->name->chars);
        }
    }

    resetStack();
}
static void defineNative(const char* name, NativeFn function) {
    push(OBJ_VAL(copyString(name, (int)strlen(name))));
    push(OBJ_VAL(newNative(function)));
    tableSet(&vm.globals, AS_STRING(vm.stack[0]), vm.stack[1]);
    pop();
    pop();
}

// Initializes the virtual machine
void initVM(){
    resetStack();
    vm.objects = NULL;
    initTable(&vm.globals);
    initTable(&vm.strings);

    defineNative("pow", powNative);
    defineNative("modulo", moduloNative);
    defineNative("sum", sumNative);
    defineNative("product", productNative);
    defineNative("log", logNative);
    defineNative("file_write", fileWriteNative);
    //defineNative("file_read", fileReadNative);
    defineNative("file_append", fileAppendNative);
    defineNative("new_dir", newDirNative);
    defineNative("cmd", cmdNative);
    defineNative("clock", clockNative);
    defineNative("sys_exit", sysExitNative);
    defineNative("as_double", asDoubleNative);
    defineNative("as_int", asIntNative);
    /*
    defineNative("as_str", asStrNative);
    defineNative("char_at", charAtNative);
    defineNative("len", lenNative);
    defineNative("sub_str", subStrNative);
    defineNative("trim", trimNative);
     */
}

// Frees the virtual machine
void freeVM(){
    freeTable(&vm.globals);
    freeTable(&vm.strings);
    freeObjects();
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

static bool call(ObjFunction* function, int argCount) {
    if (argCount != function->arity) {
        runtimeError("Expected %d arguments but got %d.",
                     function->arity, argCount);
        return false;
    }

    if (vm.frameCount == FRAMES_MAX) {
        runtimeError("Stack overflow.");
        return false;
    }

    CallFrame* frame = &vm.frames[vm.frameCount++];
    frame->function = function;
    frame->ip = function->chunk.code;
    frame->slots = vm.stackTop - argCount - 1;
    return true;
}
static bool callValue(Value callee, int argCount) {
    if (IS_OBJ(callee)) {
        switch (OBJ_TYPE(callee)) {
            case OBJ_FUNCTION: // [switch]
                return call(AS_FUNCTION(callee), argCount);
            case OBJ_NATIVE: {
                NativeFn native = AS_NATIVE(callee);
                Value result = native(argCount, vm.stackTop - argCount);
                vm.stackTop -= argCount + 1;
                push(result);
                return true;
            }
            default:
                break; // Non-callable object type.
        }
    }
    runtimeError("Can only call functions and classes.");
    return false;
}
static bool isFalsey(Value value){
    return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

static void concatenate(){
    ObjString* b = AS_STRING(pop());
    ObjString* a = AS_STRING(pop());
    int length = a->length + b->length;
    char* chars = ALLOCATE(char, length + 1);
    memcpy(chars, a->chars, a->length);
    memcpy(chars + a->length, b->chars, b->length);
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    push(OBJ_VAL(result));
}

// runs the virtual machine
static InterpretResult run(){
    CallFrame* frame = &vm.frames[vm.frameCount - 1];

#define READ_BYTE() (*frame->ip++)

#define READ_SHORT() \
    (frame->ip += 2, \
    (uint16_t)((frame->ip[-2] << 8) | frame->ip[-1]))

#define READ_CONSTANT() \
    (frame->function->chunk.constants.values[READ_BYTE()])

#define READ_STRING() AS_STRING(READ_CONSTANT())
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
       }       \
       else {   \
              runtimeError("Operands must be either both integer or both double numbers.");                \
               return INTERPRET_RUNTIME_ERROR;       \
       }              \
       }while(false)
#define BINARY_OP_COMPARISON(op) \
  do {                \
       if (IS_INT(peek(0)) && IS_INT(peek(1))){                                                \
            int b = AS_INT(pop());         \
            int a = AS_INT(pop());                                                             \
            push(BOOL_VAL(a op b));      \
       } else if (IS_DOUBLE(peek(0)) && IS_DOUBLE(peek(1))) {                                  \
            double b = AS_DOUBLE(pop());         \
            double a = AS_DOUBLE(pop());                                                             \
            push(BOOL_VAL(a op b));      \
       }       \
       else {   \
              runtimeError("Operands must be either both integer or both double numbers.");                \
               return INTERPRET_RUNTIME_ERROR;       \
       }              \
       }while(false)
#ifdef  DEBUG_TRACE_EXECUTION
    printf("         ");
    for(Value* slot = vm.stack; slot < vm.stackTop; slot++){
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\n");
    disassembleInstruction(&frame->function->chunk,
                           (int)(frame->ip - frame->function->chunk.code));
#endif
    for(;;){
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_NIL:
                push(NIL_VAL);
                break;
            case OP_TRUE:
                push(BOOL_VAL(true));
                break;
            case OP_FALSE:
                push(BOOL_VAL(false));
                break;
            case OP_POP:
                pop();
                break;
            case OP_GET_LOCAL: {
                uint8_t slot = READ_BYTE();
                push(frame->slots[slot]);
                break;
            }
            case OP_SET_LOCAL: {
                uint8_t slot = READ_BYTE();
                frame->slots[slot] = peek(0);
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;
                if (!tableGet(&vm.globals, name, &value)) {
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(value);
                break;
            }
            case OP_DEFINE_GLOBAL: {
                ObjString* name = READ_STRING();
                tableSet(&vm.globals, name, peek(0));
                pop();
                break;
            }
            case OP_SET_GLOBAL: {
                ObjString* name = READ_STRING();
                if (tableSet(&vm.globals, name, peek(0))) {
                    tableDelete(&vm.globals, name); // [delete]
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_GREATER:
                BINARY_OP_COMPARISON(>);
                break;
            case OP_LESS:
                BINARY_OP_COMPARISON(<);
                break;
            case OP_ADD: {
                if (IS_STRING(peek(0)) && IS_STRING(peek(1))) {
                    concatenate();
                } else {
                    BINARY_OP(+);
                }
            }
                break;
            case OP_SUBTRACT:
                BINARY_OP(-);
                break;
            case OP_MULTIPLY:
                BINARY_OP(*);
                break;
            case OP_DIVIDE:
                BINARY_OP(/);
                break;
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_NEGATE:
                if (!IS_INT(peek(0)) || !IS_DOUBLE(peek(0))) {
                    runtimeError("Operand must be a number (int/double).");
                    return INTERPRET_RUNTIME_ERROR;
                }
                if (IS_INT(peek(0))) {
                    push(INT_VAL(-AS_INT(pop())));
                } else {
                    push(DOUBLE_VAL(-AS_DOUBLE(pop())));
                }
                break;
            case OP_PRINT: {
                printValue(pop());
                printf("\n");
                break;
            }
            case OP_JUMP: {
                uint16_t offset = READ_SHORT();
                frame->ip += offset;
                break;
            }
            case OP_JUMP_IF_FALSE: {
                uint16_t offset = READ_SHORT();
                if (isFalsey(peek(0))) frame->ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = READ_SHORT();
                frame->ip -= offset;
                break;
            }
            case OP_CALL: {
                int argCount = READ_BYTE();
                if (!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame = &vm.frames[vm.frameCount - 1];
                break;
            }
            case OP_RETURN: {
                Value result = pop();
                vm.frameCount--;
                if (vm.frameCount == 0) {
                    pop();
                    return INTERPRET_OK;
                }

                vm.stackTop = frame->slots;
                push(result);
                frame = &vm.frames[vm.frameCount - 1];
                break;
            }
        }
    }

#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONSTANT
#undef READ_STRING
#undef BINARY_OP
#undef BINARY_OP_COMPARISON
}

// Interprets the chunks
InterpretResult interpret(const char* source) {
    ObjFunction* function = compile(source);
    if (function == NULL) return INTERPRET_COMPILE_ERROR;

    push(OBJ_VAL(function));
    call(function, 0);

    return run();
}
