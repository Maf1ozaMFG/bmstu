#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SEPARATORS " ,.;:'"

enum {
    ENTRY_FALSE = -1,
    START_SIZE = 1
};

typedef struct {
    char* str;
    int count;
    int textLocation;
} Word;

void swap(Word* dict, int a, int b);
int compareByCount(Word* str1, Word* str2);
int compareByLocation(Word* str1, Word* str2);

char* allocMemory();

char* getString();
int checkExist(Word* dictArray, int amount, char* word);

Word* stringSplit(char* str, int* amount);

void sortDict(Word* dict, int amount, int(*cmp)(Word*, Word*));
void sortDictByCountAndLocation(Word* dict, int amount);
void printDict(Word* dict, int amount);
void freeDict(Word* dict, int amount);


#endif // MYSTRING_H
