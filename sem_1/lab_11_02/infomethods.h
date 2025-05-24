#ifndef INFOMETHODS_H
#define INFOMETHODS_H

#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void printInvintation();
void getMode(int* m);

char* getFilePath();
FILE* openFile(const char* filePath, const char mode[3]);
void closeFile(FILE* catalog);

Music* readInfo(const char* filePath, int* countOfMusic);
void saveInfo(const char* filePath, Music* musicArr, const int countOfMusic);

#endif // INFOMETHODS_H
