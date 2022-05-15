#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include "files.h"
static bool fileExists(const char* path){
    FILE* file;
    file = fopen(path, "w");
    if(file){
        fclose(file);
        return true;
    }
    return false;
}

void fileWrite(const char* path, const char* data){
    if(fileExists(path)){
        // write to file
        FILE* file;
        file  = fopen(path, "w");
        if( file == NULL){
            fprintf(stderr, "Error writing to file '%s'.", path);
            exit(1);
        }
        fprintf(file, "%s", data);
        fclose(file);
    } else {
        fprintf(stderr, "Path '%s' doesn't exist.", path);
        exit(1);
    }
}
char* fileRead(const char* path){
    if(fileExists(path)){
        // read file
        FILE* file;
        file = fopen(path, "r");
        char* buffer = NULL;
        if(file == NULL){
            fprintf(stderr, "Error reading file '%s'.", path);
            fclose(file);
            exit(1);
        }
        fscanf(file, "%s", buffer);
        fclose(file);
        return buffer;
    } else {
        fprintf(stderr, "Path '%s' doesn't exist.", path);
        exit(1);
    }
}
void fileAppend(const char* path, const char* data){
    if(fileExists(path)){
        // write to file
        FILE* file;
        file = fopen(path, "a");
        if(file  == NULL){
            fprintf(stderr, "Error writing to file '%s'.", path);
            fclose(file);
            exit(1);
        }
        fprintf(file, "%s", data);
        fclose(file);
    } else {
        fprintf(stderr, "Path '%s' doesn't exist.", path);
        exit(1);
    }
}
void newDir(const char* path){
    if(access(path, F_OK) == -1){
        // path doesn't exit so we can create dir
        mkdir(path, S_IRWXU);
    } else {
        fprintf(stderr, "Path: '%s' already exists.", path);
        exit(1);
    }
}