#ifndef MYSTRING_H
#define MYSTRING_H

#define COUNT_OF_AMOUNT 1

#define SUCCESS 0
#define ERROR -1

int inputCount(int* n);
int countOfSpace(char* str, int len);
int findBeginningOfSurname(char* str);
void changeString(char* str, int* len, char* endToChange, int lenToChange, char* newEnd, int newLen);
void changeAllStrings(char** arrForStrings, int* lenOfString, int n, char* endToChange, char* newEnd, int lenToChange, int newLen);
void outputStrings(char** arrForStrings, int n);

void getString(char* str, int* len);
int inputStrings(char** arrForStrings, int* lenOfString, int n);


#endif // MYSTRING_H
