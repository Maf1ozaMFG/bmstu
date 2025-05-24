#include "mystring.h"

char* allocMemory() {
    return (char*)calloc(START_SIZE, sizeof(char));
}

char* getString() {
    int len = 0;
    int capacity = START_SIZE;
    char* str = allocMemory();
    char sym = (char)getchar();

    while (sym != '\n') {
        str[len++] = sym;
        if (len == capacity) {
            capacity *= 2;
            str = realloc(str, capacity);
        }
        sym = (char)getchar();
    }
    str[len] = '\0';
    return str;
}

int getMaxLen(int* maxLen) {
    return scanf("%d", maxLen);
}

Dict* stringSplit(char* str) {
    Dict* dictionary = (Dict*)calloc(1, sizeof(Dict));
    if (dictionary != NULL) {
        dictionary->amount = 0;
        char* subStr;
        int count = 0;

        subStr = strtok(str, " ");
        while (subStr) {
            count++;
            dictionary->strArray = realloc(dictionary->strArray, count * sizeof(char*));
            dictionary->lenArr = realloc(dictionary->lenArr, count * sizeof(int));

            dictionary->strArray[count - 1] = strdup(subStr);
            dictionary->lenArr[count - 1] = (int)strlen(subStr);
            dictionary->amount++;

            subStr = strtok(NULL, " ");
        }
        free(subStr);
    }
    return dictionary;
}

int existCheck(Dict* dictionary, int maxLen) {
    int result = SUCCESS;
    for (int i = 0; i < dictionary->amount; i++) {
        if (dictionary->lenArr[i] > maxLen) {
            result = ERROR;
            break;
        }
    }
    return result;
}

int spacesCheck(int strLen, int maxLen, int count) {
    return count == 1 ? 0 : maxLen - strLen;
}

void getOutputWords(Dict* dictionary, int* currWord, int maxLen) {
    int count = 0;
    int stringLen = 0;
    int checkEndResult = ERROR;
    while (*currWord + count < dictionary->amount) {
        if (stringLen + count + dictionary->lenArr[*currWord + count] <= maxLen) {
            stringLen += dictionary->lenArr[*currWord + count];
            count++;
        } else {
            break;
        }
    }
    if (*currWord + count == dictionary->amount) {
        checkEndResult = SUCCESS;
    }

    int spaces = spacesCheck(stringLen, maxLen, count);
    printStr(dictionary, *currWord, count, spaces, checkEndResult);
    *currWord += count;
}

void printStr(Dict* dictionary, int firstWord, int outputWords, int spaces, int checkEndResult) {
    if (!checkEndResult) {
        for (int i = 0; i < outputWords - 1; i++) {
            printf("%s", dictionary->strArray[firstWord + i]);
            for (int j = 0; j < spaces / (outputWords - 1); j++) {
                printf(" ");
            }
            if (spaces % (outputWords - 1) != 0) {
                printf(" ");
                spaces--;
            }
        }
        printf("%s\n", dictionary->strArray[firstWord + outputWords - 1]);
    } else {
        for (int i = 0; i < outputWords - 1; i++) {
            printf("%s ", dictionary->strArray[firstWord + i]);
        }
        printf("%s\n", dictionary->strArray[firstWord + outputWords - 1]);
    }
}

void printDict(Dict* dictionary, int maxLen) {
    int currWord = 0;
    while (currWord < dictionary->amount) {
        getOutputWords(dictionary, &currWord, maxLen);
    }
}

void freeDict(Dict* dictionary) {
    for (int i = 0; i < dictionary->amount; i++) {
        free(dictionary->strArray[i]);
    }
    free(dictionary->strArray);
    free(dictionary->lenArr);
    free(dictionary);
}



