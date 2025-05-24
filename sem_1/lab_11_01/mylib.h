#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

#define MAX_LEN 1024

enum {
    ERROR = 0,
    SUCCESS
};

char* getFilePath();

FILE* openFile(char* file, char* mode);

char* allocMemory();

int checkStrings(char* buffer);
void moveStrings(FILE* inputText, FILE* outputText);

void closeFiles(FILE* inputStream, FILE* outputStream);

#endif // MYLIB_H
