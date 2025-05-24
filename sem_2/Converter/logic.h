#ifndef LOGIC_H
#define LOGIC_H

#include "entrypoint.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 255

#define NO_ERROR "All perfect <3"
#define INCORRECT_RADIX_FROM "Choose radix From or check radix you entered"
#define INCORRECT_RADIX_TO "Choose radix To or check radix you entered"
#define OUT_OF_RANGE_RADIX "You need enter radix in range from 2 to 36"
#define NO_NUMBER "You need enter number to continue"
#define INCORRECT_VALUE "You entered wrong value"
#define OUT_OF_RANGE_NUMBER "Your number have to be in 4 byte range of int"

#define EMPTY_STRING ""
#define ZERO_VALUE "0"

#define INT_MIN -2147483648
#define INT_MAX 2147483647
#define UNSIGNED_INT_MAX 4294967295

enum SUCCESSFUL {
    ERROR = 0,
    SUCCESS
};

enum Digits {
    A = 10,
    Z = 36
};


char intToChar(unsigned int digit);
unsigned int charToInt(char sym);
char* intToString(int n);
void reverseString(char* string);
int checkForZero(AppParams* params);

unsigned int convertToDecimalNumber(char* number, int radix);
char* convertToCustomRadix(unsigned int decimalNumber, int radix);

void radixValidation(AppParams* params, AppContext* context);
void numberValidation(AppParams* params, AppContext* context);
void rangeValidation(AppParams* params, AppContext* context);

void doValidation(AppParams* params, AppContext* context);
void doConverting(AppParams* params, AppContext* context);
void doClear(AppContext* context);

#endif // LOGIC_H
