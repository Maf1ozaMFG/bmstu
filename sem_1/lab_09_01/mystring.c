#include "mystring.h"

void sortDictByCountAndLocation(Word* dict, int amount) {
    sortDict(dict, amount, compareByCount);
    sortDict(dict, amount, compareByLocation);
}

void swap(Word* dict, int a, int b) {
    Word temp = dict[a];
    dict[a] = dict[b];
    dict[b] = temp;
}

int compareByCount(Word* str1, Word* str2) {
    return str1->count < str2->count;
}

int compareByLocation(Word* str1, Word* str2) {
    return str1->count == str2->count && str1->textLocation > str2->textLocation;
}

char* allocMemory() {
    return (char*)calloc(1, sizeof(char));
}


char* getString() {
    int len = 0;
    int capacity = START_SIZE;
    char* str = allocMemory();
    char sym = getchar();

    while (sym != '\n') {
        str[len++] = tolower(sym);
        if (len == capacity) {
            capacity *= 2;
            str = realloc(str, capacity);
        }
        sym = getchar();
    }
    str[len] = '\0';
    return str;
}

int checkExist(Word* dictArray, int amount, char* word) {
    int result = ENTRY_FALSE;
    for (int i = 0; i < amount; i++) {
        if (strcmp(dictArray[i].str, word) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

Word* stringSplit(char* str, int* amount) {
    Word* dict = NULL;

    char* subStr;
    char* separators = SEPARATORS;
    int count = 0;
    int i = 0;

    subStr = strtok(str, separators);
    while (subStr) {
        int result = checkExist(dict, count, subStr);
        if (result != ENTRY_FALSE) {
            dict[result].count++;
        } else {
            count++;
            dict = (Word*)realloc(dict, count * sizeof(Word));
            dict[count - 1].str = strdup(subStr);
            dict[count - 1].count = 1;
            dict[count - 1].textLocation = i;
        }
        subStr = strtok(NULL, separators);
        i++;
    }
    *amount = count;
    free(subStr);
    return dict;
}

void sortDict(Word* dict, int amount, int(*cmp)(Word*, Word*)) {
    for (int i = 0; i < amount - 1; i++) {
        for (int j = i + 1; j < amount; j++) {
            if (cmp(dict + i, dict + j) > 0) {
                swap(dict, i, j);
            }
        }
    }
}

void printDict(Word* dict, int amount) {
    for (int i = 0; i < amount; i++) {
        printf("%s: %d\n", dict[i].str, dict[i].count);
    }
}

void freeDict(Word* dict, int amount) {
    for (int i = 0; i < amount; i++) {
        free(dict[i].str);
    }
    free(dict);
}
