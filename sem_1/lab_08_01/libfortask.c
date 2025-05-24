#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

char* allocMemory() {
    return (char*)malloc(sizeof(char));
}

char* reallocMemory(char* s, const int len) {
    return (char*)realloc(s, len * sizeof(char));
}

char* getString() {
    int len = 0;
    int capacity = 1;
    char* s = allocMemory();
    char c = getchar();

    while (c != '\n') {
        *(s + (len++)) = c;
        if (len >= capacity) {
            capacity *= 2;
            s = reallocMemory(s, capacity);
        }
        c = getchar();
    }

    *(s + len) = '\0';
    return s;

}

char* delSpace(char* s) {
    int len = myStrlen(s);
    for (int i = 0; i < len; i++) {
        if (*(s + i) == ' ') {
            while (*(s + i + 1) == ' ') {
                for (int j = i; j < len; j++) {
                    *(s + j) = *(s + j + 1);
                }
            }
        }
    }

    for (int i = 0; i < len; i++) {
        if (*(s + i) == ' ') {
            if (myStrcspn(*(s + i + 1), ",.?!;:()-") != TRUE) {
                for (int j = i; j < len; j++) {
                    *(s + j) = *(s + j + 1);
                }
            }
        }
    }

    if (s[0] == ' ') {
        for (int i = 0; i < len; i++) {
            *(s + i) = *(s + i + 1);
        }
    }

    if (*(s + myStrlen(s) - 1) == ' ') {
        *(s + myStrlen(s) - 1) = '\0';
    }
    return s;
}

void freeString(char* s) {
    free(s);
}
