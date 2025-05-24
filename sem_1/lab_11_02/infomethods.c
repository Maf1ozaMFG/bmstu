#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void printInvintation() {
    printf("Select mode:\n"
           "1 - Add new music\n"
           "2 - Show all songs\n"
           "3 - Sort music by name\n"
           "4 - Delete music by artist\n"
           "5 - Exit\n");
}

void getMode(int* m) {
    fflush(stdin);
    *m = (int)(getchar() - '0');
    getchar();
}

char* getFilePath() {
    char* result;
    printf("Enter file path: ");
    char* filePath = (char*)calloc(LEN, sizeof(char));
    int checkFilePath = scanf("%s", filePath);
    if (filePath != NULL && checkFilePath) {
        result = filePath;
    } else {
        result = NULL;
    }
    return result;
}

FILE* openFile(const char* filePath, const char mode[3]) {
    return fopen(filePath, mode);
}

void closeFile(FILE* catalog) {
    fflush(stdin);
    fclose(catalog);
}

Music* readInfo(const char* filePath, int* countOfMusic) {
    Music* musicArr = allocMemory();
    FILE* catalog = openFile(filePath, "r");

    if (catalog) {
        Music readMusic;
        while ((fgets(readMusic.name, LEN, catalog)) != NULL) {
            (*countOfMusic)++;
            musicArr = reallocMemory(musicArr, *countOfMusic);
            fgets(readMusic.artist, LEN, catalog);
            fscanf(catalog, "%d\n", &readMusic.duration);
            fscanf(catalog, "%d\n", &readMusic.rank);

            *(musicArr + *countOfMusic - 1) = readMusic;

        }
    } else {
        printf("Error: File SSSSSSunreadable\n");
        free(musicArr);
        musicArr = NULL;
        countOfMusic = 0;
    }
    closeFile(catalog);
    return musicArr;
}

void saveInfo(const char* filePath, Music* musicArr, const int countOfMusic) {
    FILE *catalog = openFile(filePath, "w");

    if (catalog) {
        for (int i = 0; i < countOfMusic; i++) {
            fputs(musicArr[i].name, catalog);
            fputs(musicArr[i].artist, catalog);
            fprintf(catalog, "%d\n", musicArr[i].duration);
            fprintf(catalog, "%d\n", musicArr[i].rank);
        }
    } else {
        printf("Error saving: Can't open file\n");
    }
    closeFile(catalog);
}
