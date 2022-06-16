#include <stdlib.h>
#include <time.h>
#include "os.h"

void cmd_(const char* command){
    system(command);
}

double clock_(){
    return (double)(clock()/CLOCKS_PER_SEC);
}

void sysExit(int code){
    exit(code);
}