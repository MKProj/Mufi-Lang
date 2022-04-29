#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

//> Major version of mufi
#define MAJOR 0
//> Minor version of mufi
#define MINOR 1
//> Patch version of mufi
#define PATCH 0
//> Codename of release
#define CODENAME "Baloo"
//> Declares the version
#define VERSION() (printf("Mufi Version %d.%d.%d (%s Release)\n", MAJOR, MINOR, PATCH, CODENAME))
//> Mufi read-eval-print-loop function
static void repl(){
    char line [1024];
    VERSION();
    for(;;){
        printf("(mufi) >> ");
        if (!fgets(line, sizeof(line), stdin)){
            printf("\n");
            break;
        }
        interpret(line);
    }
}
//> From path reads files characters and returns it
static char* readFile(const char* path){
    FILE* file = fopen(path, "rb");
    if (file == NULL){
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize+1);
    if (buffer == NULL){
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize){
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }
    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}
//> Runs the source code of a file
static void runFile(const char* path){
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if(result ==  INTERPRET_COMPILE_ERROR) exit(65);
    if(result == INTERPRET_RUNTIME_ERROR) exit(70);
}


int main(int argc, const char* argv[]){
    initVM();

    if(argc == 1){
        repl();
    } else if (argc == 2){
        if (*argv[1] == 'v'){
            VERSION();
        }
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: mufi <path>\n");
        exit(64);
    }

    freeVM();
    return 0;
}