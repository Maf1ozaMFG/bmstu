#include <stdio.h>
#include <stdlib.h>


#define SUCCESS 0
#define ERROR 1

#define MAX_LEN 255

char* allocString() {
    return (char*)calloc(MAX_LEN, sizeof(char));
}

char** allocArrayForStrings(int n) {
    return (char**)calloc(n, sizeof(char*));
}

int* allocLenOfString(int n) {
    return (int*)calloc(n, sizeof(int));
}

int checkAlloc(char** arrForStrings, int* lenOfString, char* endToChange, char* newEnd) {
    int result = SUCCESS;
    if (arrForStrings == NULL || lenOfString == NULL || endToChange == NULL || newEnd == NULL) {
        result = ERROR;
        free(arrForStrings);
        free(lenOfString);
        free(endToChange);
        free(newEnd);
    }
    return result;
}

void freeMemory(char** arrForStrings, int* lenOfString, char* endToChange, char* newEnd, int n) {
    for (int i = 0; i < n; i++) {
        free(*(arrForStrings + i));
    }
    free(arrForStrings);
    free(lenOfString);
    free(endToChange);
    free(newEnd);
}

