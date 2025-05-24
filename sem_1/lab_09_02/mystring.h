#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    ERROR = 0,
    SUCCESS
};

enum {
    START_SIZE = 1
};

typedef struct {
    char** strArray;
    int* lenArr;
    int amount;
} Dict;

char* getString();
int getMaxLen(int* maxLen);

Dict* stringSplit(char* str);
int existCheck(Dict* dictionary, int maxLen);
int spacesCheck(int strLen, int maxLen, int count);
void getOutputWords(Dict* dictionary, int* currWord, int maxLen);

void printStr(Dict* dictionary, int firstWord, int outputWords, int spaces, int checkEndResult);

void printDict(Dict* dictionary, int maxLen);
void freeDict(Dict* dicionary);

char* allocMemory();
#endif // MYSTRING_H
