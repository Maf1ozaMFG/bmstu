#include <stdio.h>
#include "libfortask.h"

int main() {
    char* s = getString();
    printf("|%s|\n", s);

    char* sWithChanges = delSpace(s);
    printf("|%s|\n", sWithChanges);

    freeString(s);

    return 0;
}
