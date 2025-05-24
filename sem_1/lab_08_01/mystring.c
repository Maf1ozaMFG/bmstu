#include "mystring.h"

int myStrlen(char* s) {
    int len = 0;
    while (*(s + len) != '\0') {
        len += 1;
    }
    return len;
}

int myStrcspn(const char s1, const char* s2) {
    for (int i = 0; *(s2 + i); i++) {
        if (s1 == *(s2 + i)) {
            return i;
        }
    }
    return TRUE;
}
