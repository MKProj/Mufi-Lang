#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../object.h"
#include "conv.h"

double asDouble(Value value){
    switch(value.type){
       case  VAL_DOUBLE: return AS_DOUBLE(value); break;
       case  VAL_INT: return (double) AS_INT(value); break;
       case  VAL_NIL: return -1.0; break;
       case VAL_BOOL: {
            if(AS_BOOL(value)){
                return 0.0;
            } else {
                return 1.0;
            }
           break;
       }
       case VAL_OBJ: {
           if(IS_STRING(value)){
               char* ptr = NULL;
               char* chars = AS_CSTRING(value);
               return strtod(chars, &ptr);
           } else {
               // can only convert string objects
               return -1;
           }
           break;
       }
    }
}

int asInt(Value value){
    switch(value.type){
        case VAL_INT: return AS_INT(value); break;
        case VAL_DOUBLE: return (int) AS_DOUBLE(value);break;
        case VAL_NIL: return -1; break;
        case VAL_BOOL: {
            if(AS_BOOL(value)){
                return 0;
            } else {
                return 1;
            }
            break;
        }
        case VAL_OBJ:{
            if(IS_STRING(value)){
                char* chars = AS_CSTRING(value);
                return atoi(chars);
            } else {
                return -1;
            }
            break;
        }
    }
}

/*
char* asStr(Value value){
    switch (value.type) {
        case VAL_INT: {
            char* buffer = NULL;
            sprintf(buffer, "%d", AS_INT(value));
            return buffer;
            break;
        }
        case VAL_DOUBLE:{
            char* buffer = NULL;
            sprintf(buffer, "%g", AS_DOUBLE(value));
            return buffer;
            break;
        }
        case VAL_BOOL: {
            if(AS_BOOL(value)){
                return "true";
            } else {
                return "false";
            }
            break;
        }
        case VAL_NIL: {
            return "nil"; break;
        }
        case VAL_OBJ: {
            if(IS_STRING(value)){
                return AS_CSTRING(value);
            } else {
                return "illegal to convert";
            }
            break;
        }
    }
}
*/