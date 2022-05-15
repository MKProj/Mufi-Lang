#ifndef mufi_stdlib_files_h
#define mufi_stdlib_files_h

#include <stdio.h>
#include <stdlib.h>

void fileWrite(const char* path, const char* data);
char* fileRead(const char* path);
void fileAppend(const char* path, const char* data);
void newDir(const char* path);

#endif