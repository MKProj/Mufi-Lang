#ifndef mufi_stdlib_string_h
#define mufi_stdlib_string_h

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char charAt(char* str, int index);
int len(char* str);
char* substr(char* str, int start, int end);
char* trim(char* str);


#endif