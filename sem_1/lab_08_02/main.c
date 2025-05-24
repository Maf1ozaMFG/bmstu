#include <stdio.h>
#include "mystring.h"
#include "mylib.h"
/*
1
quembek maker wernsern
ern
abcd
*/
int main() {
    int count;
    if (!inputCount(&count)) {
        char** arrForStrings = allocArrayForStrings(count);
        int* lenOfString = allocLenOfString(count);
        char* endToChange = allocString();
        char* newEnd = allocString();
        int lenToChange, newLen;
        if (!checkAlloc(arrForStrings, lenOfString, endToChange, newEnd) && !inputStrings(arrForStrings, lenOfString, count)) {
            getString(endToChange, &lenToChange);
            getString(newEnd, &newLen);
            changeAllStrings(arrForStrings, lenOfString, count, endToChange, newEnd, lenToChange, newLen);
            outputStrings(arrForStrings, count);
            freeMemory(arrForStrings, lenOfString, endToChange, newEnd, count);
        } else {
            printf("Incorrect input\n");
        }

    } else {
        printf("Incorrect input\n");
    }
    return SUCCESS;
}
