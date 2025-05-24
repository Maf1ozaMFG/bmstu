#include "mylib.h"

int main() {
    char* inputFile = getFilePath(); /*"/Users/Valerii/Documents/lab11_1/input.txt";*/
    char* outputFile = getFilePath(); /*"/Users/Valerii/Documents/lab11_1/output.txt";*/

    if (inputFile && outputFile) {

        FILE* inputString = openFile(inputFile, "r");
        FILE* outputString = openFile(outputFile, "w");

        moveStrings(inputString, outputString);

        closeFiles(inputString, outputString);
    }
    free(inputFile);
    free(outputFile);
}

/*
/Users/626/Documents/labs/lab_11_01/input.txt
*/
