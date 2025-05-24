#include "menumethods.h"
#include "infomethods.h"

int main() {
    char* filePath = getFilePath();             //    /Users/nikitavolnuhin/Downloads/sgn3-cprog-labs-2023-bocharov-valerij-aleksandrovich-lab11/lab_11_02/catalog.txt
    int mode;
    if (filePath) {
        printInvintation();
        getMode(&mode);
        while (mode != EXIT) {
            executeSelectedMode(filePath, mode);
            printInvintation();
            getMode(&mode);
        }
    }
}

// /Users/Valerii/Documents/lab11_2/catalog.txt
