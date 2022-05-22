//
// Created by haoyangy on 5/20/2022.
//

#ifndef KV_DICT_H
#define KV_DICT_H
#define MAX_ITEM 50
#define MAX_LINE 1024

typedef struct Dict {
    char* key;
    char* value;
    struct Dict* next;
} Dict;

void add(Dict* dict, char* key, char* value);
void del(Dict* dict, char* key);
char* get(Dict* dict, char* key);
void fromFile(Dict* dictHead, char* fileName);
void toFile(Dict* dictHead, char* fileName);
void freeFrom(Dict* dictHead);
#endif //KV_DICT_H
