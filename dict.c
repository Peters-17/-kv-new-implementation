//
// Created by haoyangy on 5/20/2022.
//

#include "dict.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void strip(char* inStr){
    char* cur = inStr;
    for(;*cur != '\0';++cur)
        if(cur != inStr && (*cur == '\n' || *cur == '\r'))
            *cur = '\0';
}

void add(Dict* dictHead, char* key, char* value){
    Dict* cur = dictHead;
    while(cur->next != NULL){
        if(strncmp(cur->next->key, key, MAX_ITEM) == 0){
            strncpy(cur->next->value, value, MAX_ITEM);
            strip(cur->value);
            return;
        }
        cur = cur->next;
    }
    cur->next = (Dict*) malloc(sizeof(Dict));
    cur = cur->next;
    cur->key = (char*) malloc(sizeof(char)*MAX_ITEM);
    cur->value = (char*) malloc(sizeof(char)*MAX_ITEM);
    cur->next = NULL;
    strncpy(cur->key, key, MAX_ITEM);
    strncpy(cur->value, value, MAX_ITEM);
    strip(cur->key);
    strip(cur->value);

}

void del(Dict* dictHead, char* key){
    Dict* cur = dictHead;
    while(cur->next != NULL){
        if(strncmp(cur->next->key, key, MAX_ITEM) == 0){
            cur->next = cur->next->next;
            return;
        }
        cur = cur->next;
    }
}

char* get(Dict* dictHead, char* key){
    Dict* cur = dictHead;
    while(cur->next != NULL){
        if(strncmp(cur->next->key, key, MAX_ITEM) == 0){
            return cur->next->value;
        }
        cur = cur->next;
    }
    return NULL;
}

void toFile(Dict* dictHead, char* fileName){
    FILE* fp = stdout;
    if(fileName != NULL)
        fp = fopen(fileName, "w");
    Dict* cur = dictHead;
    while(cur->next != NULL){
        fprintf(fp, "%s,%s\n", cur->next->key, cur->next->value);
        cur = cur->next;
    }
}

void fromFile(Dict* dictHead, char* fileName){
    FILE* fp;
    if((fp = fopen(fileName, "r")) == NULL){
        fp = fopen(fileName, "w");
        fclose(fp);
        fp = fopen(fileName, "r");
    }
    char line[MAX_LINE];
    while(fgets(line, MAX_LINE, fp) != NULL){
        if(line[0] == '\0') continue;
        char* res[2];
        res[0] = strtok(line, ",");
        res[1] = strtok(NULL, ",");

        add(dictHead, res[0], res[1]);
    }

    fclose(fp);
}

void freeFrom(Dict* dictHead){
    Dict* cur = dictHead;
    while(cur != NULL){
        if(cur->key != NULL) free(cur->key);
        if(cur->value != NULL) free(cur->value);
        Dict* buf = cur;
        cur = cur->next;
        free(buf);
    }
}