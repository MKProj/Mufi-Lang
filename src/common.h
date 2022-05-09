
//> All common imports and preprocessor macros defined here 
#ifndef mufi_common_h 
#define mufi_common_h 

#include <stdbool.h>
#include <stddef.h>
#include<stdint.h>
#include <stdlib.h>

#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION

#endif

// In production, we want these debugging to be off
#undef DEBUG_TRACE_EXECUTION
#undef DEBUG_PRINT_CODE
