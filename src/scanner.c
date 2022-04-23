#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct {
    const char* start; // Start of the lexeme
    const char* current; // Current points to current char being looked at
    int line; // Current line being scanned
} Scanner;

Scanner scanner;

void initScanner(){
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}