#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAX_LINE 1024
#include "dict.h"

int main(int argc, char* argv[]) {
    Dict* dictHead = (Dict*)malloc(sizeof(Dict));
    dictHead->next = NULL;
    fromFile(dictHead, "./dic.txt");


    for(int i = 1; i < argc; i++){
        char* key;
        char* value;
        char* result;
        char* op = strtok(argv[i], ",");
        if(op[1] != '\0') return 1;
        switch (op[0]) {
            case 'p':
                key = strtok(NULL, ",");
                value = strtok(NULL, ",");
                add(dictHead, key, value);
                break;
            case 'g':
                key = strtok(NULL, ",");
                result = get(dictHead, key);
                printf("%s: %s\n", key, result == NULL? "Key not found": result);
                break;
            case 'd':
                key = strtok(NULL, ",");
                del(dictHead, key);
                break;
            case 'a':
                toFile(dictHead, NULL);
                break;
            case 'c':
                freeFrom(dictHead->next);
                dictHead->next = NULL;
                break;
            default:
                return 1;
        }
    }
    toFile(dictHead, "./dic.txt");



    return 0;
}
