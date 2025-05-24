#ifndef MYLIB_H
#define MYLIB_H

#define SUCCESS 0

char* allocString();
int* allocLenOfString(int n);
char** allocArrayForStrings(int n);
int checkAlloc(char** arrForStrings, int* lenOfString, char* endToChange, char* newEnd);
void freeMemory(char** arrForStrings, int* lenOfString, char* endToChange, char* newEnd, int n);


#endif // MYLIB_H
