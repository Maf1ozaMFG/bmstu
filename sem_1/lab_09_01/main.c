#include "mystring.h"


int main()
{
    char* string = getString();
    if (string != NULL) {
        int amount;
        Word* dict = stringSplit(string, &amount);
        if (dict != NULL) {
            sortDictByCountAndLocation(dict, amount);
            printDict(dict, amount);
        }
        freeDict(dict, amount);
    }
    free(string);
}
