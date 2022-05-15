#include "stdlib.h"


Value powNative(int argCount, Value* args){
    if(argCount != 2){
        // must have two parameters
        fprintf(stderr, "pow() only expects two parameters, %d was given.", argCount);
        return NIL_VAL;
    }
    if(args[0].type != args[1].type){
        fprintf(stderr, "pow() expects both parameters to be the same");
        return NIL_VAL;
    }
    if(args[0].type != VAL_INT && args[0].type != VAL_DOUBLE){
        fprintf(stderr, "pow() expects either both double or int values.");
        return NIL_VAL;
    }
    if(args[0].type == VAL_INT){
        return INT_VAL(powi(AS_INT(args[0]), AS_INT(args[1])));
    } else {
        return DOUBLE_VAL(powd(AS_DOUBLE(args[0]), AS_DOUBLE(args[1])));
    }
}
Value moduloNative(int argCount, Value* args){
    if(argCount != 2){
        // must have two parameters
        fprintf(stderr, "modulo() only expects two parameters.");
        return NIL_VAL;
    }
    if(args[0].type != args[1].type){
        fprintf(stderr, "modulo() expects both parameters to be the same");
        return NIL_VAL;
    }
    if(args[0].type != VAL_INT){
        fprintf(stderr, "modulo() expects values to be integers.");
        return NIL_VAL;
    }
    return INT_VAL(modulo(AS_INT(args[0]), AS_INT(args[1])));
}
Value sumNative(int argCount, Value* args){
    double doubArgs[argCount];
    // checks the type for sums
    ValueType type = args[0].type;
    if(type != VAL_INT && type != VAL_DOUBLE){
        fprintf(stderr, "All values in sum() must be double or int.");
        return NIL_VAL;
    }
    for(int i=0; i < argCount; i++){
        if(args[i].type != type){
            fprintf(stderr, "All values in sum() must be the same.");
            return NIL_VAL;
        }
        if (args[i].type == VAL_DOUBLE){
            doubArgs[i] = AS_DOUBLE(args[i]);
        } else {
            doubArgs[i] = (double) AS_INT(args[i]);
        }
    }
    double s = sum((double*)doubArgs);
    if(type ==VAL_INT){
        return INT_VAL((int)s);
    } else {
        return DOUBLE_VAL(s);
    }
}
Value productNative(int argCount, Value* args){
    double doubArgs[argCount];
    // checks the type for product
    ValueType type = args[0].type;
    if(type != VAL_INT && type != VAL_DOUBLE){
        fprintf(stderr, "All values in product() must be double or int.");
        return NIL_VAL;
    }
    for(int i=0; i < argCount; i++){
        if(args[i].type != type){
            fprintf(stderr, "All values in product() must be the same.");
            return NIL_VAL;
        }
        if (args[i].type == VAL_DOUBLE){
            doubArgs[i] = AS_DOUBLE(args[i]);
        } else {
            doubArgs[i] = (double) AS_INT(args[i]);
        }
    }
    double p = product((double*)doubArgs);
    if(type ==VAL_INT){
        return INT_VAL((int)p);
    } else {
        return DOUBLE_VAL(p);
    }
}
Value logNative(int argCount, Value* args){
    if(argCount != 2){
        fprintf(stderr, "log() expects 2 parameters, %d was given.", argCount);
        return NIL_VAL;
    }
    if(args[0].type != args[1].type && args[0].type != VAL_DOUBLE){
        fprintf(stderr, "log() only accepts double values.");
        return NIL_VAL;
    }
    return DOUBLE_VAL(log_(AS_DOUBLE(args[0]), AS_DOUBLE(args[1])));
}

Value fileWriteNative(int argCount, Value* args){
    if(args[0].type == args[1].type && IS_STRING(args[0])){
        fileWrite(AS_CSTRING(args[0]), AS_CSTRING(args[1]));
        return INT_VAL(0);
    } else {
        return INT_VAL(-1);
    }
}
/*
Value fileReadNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "file_read() expects only 1 parameter, %d was given.", argCount);
        return INT_VAL(-1);
    }
    if(IS_STRING(args[0])) {
        char* data = fileRead(AS_CSTRING(args[0]));
        ObjString obj = NULL;
        obj->chars = data;
        obj->length = sizeof(data);
        return OBJ_VAL(obj);
    } else {
        fprintf(stderr, "file_read() only accepts a string path.");
        return INT_VAL(-1);
    }
}
*/
Value fileAppendNative(int argCount, Value* args){
    if(args[0].type == args[1].type && IS_STRING(args[0])){
        fileAppend(AS_CSTRING(args[0]), AS_CSTRING(args[1]));
        return INT_VAL(0);
    } else {
        return INT_VAL(-1);
    }
}
Value newDirNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "new_dir() expects only 1 parameter, %d was given.", argCount);
        return INT_VAL(-1);
    }
    if(IS_STRING(args[0])) {
        newDir(AS_CSTRING(args[0]));
        return INT_VAL(0);
    } else {
        fprintf(stderr, "new_dir() only accepts a string path.");
        return INT_VAL(-1);
    }
}

Value cmdNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "cmd() expects only 1 parameter, %d was given.", argCount);
        return INT_VAL(-1);
    }
    if(IS_STRING(args[0])){
        cmd_(AS_CSTRING(args[0]));
        return NIL_VAL;
    } else {
        fprintf(stderr, "cmd() only accepts a string command.");
        return INT_VAL(-1);
    }
}
Value clockNative(int argCount, Value* args){
    if(argCount != 0){
        fprintf(stderr, "clock() doesn't accept any parameters, %d was given.", argCount);
        return DOUBLE_VAL(0.0);
    }
    return DOUBLE_VAL(clock_());
}
Value sysExitNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "sys_exit() expects only 1 parameter, %d was given.", argCount);
        return NIL_VAL;
    }
    if(IS_INT(args[0])){
        sysExit(AS_INT(args[0]));
        return NIL_VAL;
    } else {
        return NIL_VAL;
    }
}


Value asDoubleNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "as_double() only accepts 1 parameter, %d was given", argCount);
        return NIL_VAL;
    }
    return DOUBLE_VAL(asDouble(args[0]));
}
Value asIntNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "as_int() only accepts 1 parameter, %d was given", argCount);
        return NIL_VAL;
    }
    return INT_VAL(asInt(args[0]));
}
/*
Value asStrNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "as_string() only accepts 1 parameter, %d was given", argCount);
        return NIL_VAL;
    }
    char* as = asStr(args[0]);
    return OBJ_VAL(copyString(as, sizeof(as)));
}
 */
/*
Value charAtNative(int argCount, Value* args){
    if(argCount != 2){
        fprintf(stderr, "char_at() only accepts 2 parameters, %d was given.", argCount);
        return NIL_VAL;
    }
    char* str = NULL;
    int index = 0;
    if(IS_STRING(args[0]) && IS_INT(args[1])){
        str = AS_CSTRING(args[0]);
        index = AS_INT(args[1]);
        char c = charAt(str, index);
        return OBJ_VAL(copyString(&c, 1));
    } else {
        fprintf(stderr, "Error in types, you must put: char_at(string str, int index)");
        return NIL_VAL;
    }

}
Value lenNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "len() only accepts 1 parameter, %d was given.", argCount);
        return INT_VAL(0);
    }
    if(IS_STRING(args[0])){
        int length = len(AS_CSTRING(args[0]));
        return INT_VAL(length);
    } else {
        fprintf(stderr, "len() only accepts string values.");
        return INT_VAL(0);
    }
}
Value subStrNative(int argCount, Value* args){
    if(argCount != 3){
        fprintf(stderr, "sub_str() only accepts 3 parameters, %d was given.", argCount);
        return NIL_VAL;
    }
    if(IS_STRING(args[0]) && IS_INT(args[1]) && IS_INT(args[2])){
        char* sub = substr(AS_CSTRING(args[0]), AS_INT(args[1]), AS_INT(args[2]));
        return OBJ_VAL(copyString(sub, sizeof(sub)));
    } else {
        fprintf(stderr, "Error in types, you must put subs_str(string str, int start, int end).");
        return NIL_VAL;
    }
}
Value trimNative(int argCount, Value* args){
    if(argCount != 1){
        fprintf(stderr, "trim() only accepts 1 parameter, %d was given.", argCount);
        return NIL_VAL;
    }
    if(IS_STRING(args[0])){
       char* str = trim(AS_CSTRING(args[0]));
        return OBJ_VAL(copyString(str, sizeof(str)));
    } else {
        fprintf(stderr, "trim() only accepts string values.");
        return INT_VAL(0);
    }
}
 */