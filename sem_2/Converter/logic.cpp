#include "logic.h"
#include "entrypoint.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void doValidation(AppParams* params, AppContext* context) { //&&&&&&&&&
    strncpy(context->validationState, NO_ERROR, SIZE);
    radixValidation(params, context);
    numberValidation(params, context);
    rangeValidation(params, context);
}

void checkRadixForExistance(AppParams* params, AppContext* context) {
    if (!strcmp(params->radixFrom, "")) {
        strncpy(context->validationState, INCORRECT_RADIX_FROM, SIZE);
        params->validationState = ERROR;
    } else if (!strcmp(params->radixTo, "")) {
        strncpy(context->validationState, INCORRECT_RADIX_TO, SIZE);
        params->validationState = ERROR;
    }
}

void radixValidation(AppParams* params, AppContext* context) {
    char etalon[] = "0123456789";
    checkRadixForExistance(params, context);
    if (params->validationState) {
        for (int i = 0; i < (int)strlen(params->radixFrom); i++) {
            char* sym = strchr(etalon, params->radixFrom[i]);
            if (sym == NULL) {
                strncpy(context->validationState, INCORRECT_RADIX_FROM, SIZE);
                params->validationState = ERROR;
                break;
            }
        }
        for (int i = 0; i < (int)strlen(params->radixTo); i++) {
            char* sym = strchr(etalon, params->radixTo[i]);
            if (sym == NULL) {
                strncpy(context->validationState, INCORRECT_RADIX_TO, SIZE);
                params->validationState = ERROR;
                break;
            }
        }
    }
    if (params->validationState) {
        int radixFrom = atoi(params->radixFrom);
        int radixTo = atoi(params->radixTo);

        if (radixFrom < MINRADIX || radixFrom > MAXRADIX || radixTo < MINRADIX || radixTo > MAXRADIX) {     //check availability of radix
            strncpy(context->validationState, OUT_OF_RANGE_RADIX, SIZE);
            params->validationState = ERROR;
        }
    }
}

void checkValueForExistance(AppParams* params, AppContext* context) {
    if (!strcmp(params->initValue, "") || !strcmp(params->initValue, "-") || !strcmp(params->initValue, "+")) {
        params->validationState = ERROR;
        strncpy(context->validationState, NO_NUMBER, SIZE);
    }
}

void numberValidation(AppParams* params, AppContext* context) {
    checkValueForExistance(params, context);
    if (params->validationState) {
        int radix = atoi(params->radixFrom);
        char availableRadixes[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = (atoi(params->radixFrom) == 10 && (params->initValue[0] == '-' || params->initValue[0] == '+')); i < (int)strlen(params->initValue); i++) {
            char* symbol = strchr(availableRadixes, params->initValue[i]);
            if (symbol - availableRadixes >= radix || symbol == NULL) {
                params->validationState = ERROR;
                strncpy(context->validationState, INCORRECT_VALUE, SIZE);
                break;
            }
        }
    }
}

void decimalRangeValidation(AppParams* params, AppContext* context) {
    char* end;
    long int number = strtol(params->initValue, &end, 10);
    if (number < INT_MIN || number > INT_MAX) {
        params->validationState = ERROR;
        strncpy(context->validationState, OUT_OF_RANGE_NUMBER, SIZE);
    }
}

void nonDecimalRangeValidation(AppParams* params, AppContext* context) {
    int radix = atoi(params->radixFrom);
    unsigned long int number = 0;

    for (int i = 0; i < (int)strlen(params->initValue); i++) {
        int digit = charToInt(params->initValue[i]);
        number += digit * pow(radix, (int)strlen(params->initValue) - i - 1);
        if (number > (unsigned int)UNSIGNED_INT_MAX) {
            params->validationState = ERROR;
            strncpy(context->validationState, OUT_OF_RANGE_NUMBER, SIZE);
            break;
        }
    }
}

void rangeValidation(AppParams* params, AppContext* context) {
    if (params->validationState) {
        int radix = atoi(params->radixFrom);

        if (radix == 10) {
            decimalRangeValidation(params, context);
        } else {
            nonDecimalRangeValidation(params, context);
        }
    }
}

void doConverting(AppParams* params, AppContext* context) { //&&&&&&&&&
    strncpy(context->resultValue, EMPTY_STRING, SIZE);
    if (params->validationState) {
        if (checkForZero(params)) {
            strncpy(context->resultValue, ZERO_VALUE, SIZE);
        } else {
            unsigned int decimalNumber = convertToDecimalNumber(params->initValue, atoi(params->radixFrom));
            if (decimalNumber) {
                char* resultValue = convertToCustomRadix(decimalNumber, atoi(params->radixTo));
                strncpy(context->resultValue, resultValue, SIZE);
                free(resultValue);
            } else {
                strncpy(context->resultValue, EMPTY_STRING, SIZE);
            }
        }
    }
}

unsigned int convertToDecimalNumber(char* number, int radix) {
    unsigned int decimalNumber = 0;

    if (radix == 10) {
        decimalNumber = (unsigned)atoi(number);
    } else {
        for (int i = (int)strlen(number) - 1; i >= 0; i--) {
            decimalNumber += charToInt(number[i]) * pow(radix, (int)strlen(number) - i - 1);
        }
    }

    return decimalNumber;
}

char* convertToCustomRadix(unsigned int decimalNumber, int radix) {
    char* result = (char*)calloc(SIZE, sizeof(char));

    if (radix == 10) {
        int decimalNumberWithSign = (int)decimalNumber;
        char* tempValue = intToString(decimalNumberWithSign);
        strncpy(result, tempValue, SIZE);
        free(tempValue);
    } else {
        while (decimalNumber) {
            int tempResult = decimalNumber % radix;
            result[strlen(result)] = intToChar(tempResult);
            decimalNumber /= radix;
        }
        reverseString(result);
    }

    return result;
}


unsigned int charToInt(char sym) {
    return (sym >= '0' && sym <= '9') ? (sym - '0') : (sym >= 'A' && sym <= 'F') ? (sym - 'A' + 10) : -1;
}


char intToChar(unsigned int digit) {
    return (digit >= 0 && digit <= 9) ? ('0' + digit) : (digit >= A && digit <= Z) ? ('A' + digit - 10) : '!';
}

void cutExtraZero(char* string) {
    for (int i = strlen(string) - 1; i > 0; i--) {
        if (string[i] == '0') {
            string[i] = '\n';
        }
    }
}

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void reverseString(char* string) {
    for (int i = string[0] == '-'; i < (int)strlen(string) / 2; i++) {
        swap(string + (strlen(string) - i - 1), string + i);
    }
}

char* intToString(int n) {
    char* string = (char*)calloc(SIZE, sizeof(char));
    if (n < 0) {
        string[0] = '-';
    }
    while (n) {
        string[strlen(string)] = intToChar(abs(n % 10));
        n /= 10;
    }
    cutExtraZero(string);
    reverseString(string);

    return string;
}

int checkForZero(AppParams* params) {
    int checkResult = SUCCESS;

    for (int i = (atoi(params->radixFrom) == 10 && (params->initValue[0] == '-' || params->initValue[0] == '+')); i < (int)strlen(params->initValue); i++) {
        if (params->initValue[i] != '0') {
            checkResult = ERROR;
            break;
        }
    }

    return checkResult;
}

void doClear(AppContext* context) {
    strncpy(context->resultValue, EMPTY_STRING, SIZE);
    strncpy(context->validationState, EMPTY_STRING, SIZE);
}
