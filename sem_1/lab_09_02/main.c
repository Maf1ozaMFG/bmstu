#include "mystring.h"


int main() {
    char* string = getString();
    if (string != NULL) {
        int maxLen;
        if (getMaxLen(&maxLen)) {
            Dict* dictionary = stringSplit(string);
            if (dictionary != NULL && existCheck(dictionary, maxLen)) {
                printDict(dictionary, maxLen);
            } else {
                printf("Incorrect input");
            }
            freeDict(dictionary);
        } else {
            printf("Incorrect input");
        }
    } else {
        printf("Incorrect input");
    }
    free(string);
}
