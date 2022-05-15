#include "string.h"
#include <stdbool.h>

char charAt(char* str, int index){
    return str[(size_t)index];
}

int len(char* str){
    return (int)sizeof(str);
}

char* substr(char* str, int start, int end){
    char* substr = NULL;
    for(int i=start; i < end + 1; i++){
        for(int j = 0; j < end+1; j++){
            substr[j] = str[i];
        }
    }
    return substr;
}

static bool isWhiteSpace(char c){
    return c == ' ';
}

char* trim(char* str){
    char* newStr= NULL;
    int count = 0;
    char c = str[count];
    while(!isWhiteSpace(c) && count < sizeof(str)){
        newStr[count] = c;
        count += 1;
        c = str[count];
    }
    return newStr;
}
