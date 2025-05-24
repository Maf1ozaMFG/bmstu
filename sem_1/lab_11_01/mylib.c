#include "mylib.h"

FILE* openFile(char* file, char* mode) {
    return fopen(file, mode);
}

char* getFilePath() {
    char* result;
    printf("Enter file path: \n");
    char* filePath = allocMemory();
    int result = scanf("%s", filePath);
    if (filePath != NULL && result) {
        result = filePath;
    } else {
        result = NULL;
    }
    return result;
}

char* allocMemory() {
    return (char*)malloc(MAX_LEN * sizeof(char));
}

int checkStrings(char* buffer) {
    int result = ERROR;
    if (buffer[0] != '\n') {
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\n') {
                result = SUCCESS;
                break;
            }
        }
    }
    return result;
}

void moveStrings(FILE* inputText, FILE* outputText) {
    if (inputText && outputText) {
        char* buffer = allocMemory();
        int n = 1;
         while ((fgets(buffer, MAX_LEN, inputText)) != NULL) {
             if (checkStrings(buffer)) {
                 fprintf(outputText, "%d. ", n);
                 fprintf(stdout, "%d. %s", n, buffer);
                 fputs(buffer, outputText);
                 n++;
             }
         }
         free(buffer);
     }
}

void closeFiles(FILE* inputStream, FILE* outputStream) {
    fclose(inputStream);
    fclose(outputStream);
}
