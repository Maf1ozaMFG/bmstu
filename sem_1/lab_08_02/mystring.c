#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

#define COUNT_OF_AMOUNT 1

#define SUCCESS 0
#define ERROR -1

int inputCount(int* n) {
    int result = ERROR;
    int a = scanf("%d\n", n);
    if (a == COUNT_OF_AMOUNT && *n > 0) {
        result = SUCCESS;
    }
    return result;
}

void getString(char* str, int* len) {
    *len = 0;
    char c = getchar();
    while (c != '\n') {
        str[(*len)++] = c;
        c = getchar();
    }
    str[*len] = '\0';
}

int countOfSpace(char* str, int len) {
    int countOfSpace = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
        countOfSpace++;
        }
    }
    return countOfSpace;
}

int inputStrings(char** arrForStrings, int* lenOfString, int n) {
    int result = SUCCESS;
    for (int i = 0; i < n; i++) {
        *(arrForStrings + i) = allocString();
        getString(*(arrForStrings + i), lenOfString + i);
        if (countOfSpace(*(arrForStrings + i), *(lenOfString + i)) != 2) {
            result = ERROR;
            break;
        }
    }
    return result;
}

int findBeginningOfSurname(char* str) {
    int countOfChar = 0;
    int countOfSpaces = 0;
    for (; countOfSpaces < 2; countOfChar++) {
        if (str[countOfChar] == ' ') {
            countOfSpaces++;
        }
    }
    return countOfChar;
}

void changeString(char* str, int* len, char* endToChange, int lenToChange, char* newEnd, int newLen) {
    int beginningOfSurname = findBeginningOfSurname(str);
    int result = SUCCESS;
    if (*len - beginningOfSurname <= 0 || *len - lenToChange <= beginningOfSurname) {
        result = ERROR;
    }
    for (int i = 0; i < lenToChange; i++) {
        if (str[*len - i - 1] != endToChange[lenToChange - i - 1]) {
            result = ERROR;
        }
    }
    if (!result) {
        for (int j = 0; j < newLen; j++) {
            str[*len - lenToChange + j] = newEnd[j];
        }
        *len = *len - lenToChange + newLen;
        str[*len] = '\0';
    }
}

void changeAllStrings(char** arrForStrings, int* lenOfString, int n, char* endToChange, char* newEnd, int lenToChange, int newLen) {
    for (int i = 0; i < n; i++) {
        changeString(*(arrForStrings + i), lenOfString + i, endToChange, lenToChange, newEnd, newLen);
    }
}

void outputStrings(char** arrForStrings, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", *(arrForStrings + i));
    }
}
