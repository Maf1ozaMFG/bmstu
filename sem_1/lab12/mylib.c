#include "mylib.h"
#include "mystring.h"


void printInvitation() {
    printf("Select command\n"
           "1 - Add new music\n"
           "2 - Show all music\n"
           "3 - Sort music by rank and name\n"
           "4 - Delete music of artist\n"
           "5 - Exit\n\n");
}


int getCommand() {
    fflush(stdin);
    int c = (getchar() - '0');
    getchar();
    return c;
}

int readMusicFromFile(FILE* catalog, Music* readMusic, int step) {
    fseek(catalog, step * sizeof(Music), SEEK_SET);
    return fread(readMusic, sizeof(Music), 1, catalog);
}

void writeMusicToFile(FILE* catalog, Music* readMusic, int step) {
    fseek(catalog, step * sizeof(Music), SEEK_SET);
    fwrite(readMusic, sizeof(Music), 1, catalog);
}

char* getFilePath() {
    char* result;
    printf("Enter file path: \n");
    char* filePath = (char*)calloc(LEN, sizeof(char));
    int checkFilePath = scanf("%s", filePath);
    if (filePath != NULL && checkFilePath) {
       result = filePath; 
    } else {
        result = NULL;
    }
    return result;
}

FILE* openFile(const char* filePath, char* mode) {
    return fopen(filePath, mode);
}

void closeFile(FILE* catalog) {
    rewind(catalog);
    fflush(stdin);
    fclose(catalog);
}

void printMusic(Music readMusic) {
    printf("Music name: %s", readMusic.name);
    printf("Music artist: %s", readMusic.artist);
    printf("Music duration: %d\n", readMusic.duration);
    printf("Music rank: %d\n", readMusic.rank);
    puts("");
}

int countCheck(const char* filePath) {
    int count = 0;
    FILE* catalog = openFile(filePath,"rb");

    if (catalog) {
        Music readMusic;

        while ((fread(&readMusic, sizeof(Music), 1, catalog)) != 0) {       //reading another Music
            count++;
        }
    } else {
        printf("Error opening the file");
    }
    closeFile(catalog);

    return count;
}


void swap(FILE* catalog, int a, int b) {         //changing 2 Musics
    Music temp1, temp2;

    readMusicFromFile(catalog, &temp1, a);
    readMusicFromFile(catalog, &temp2, b);

    writeMusicToFile(catalog, &temp2, a);
    writeMusicToFile(catalog, &temp1, b);
}


int readMusic(Music* newMusic) {
    int result = SUCCESS;

    printf("Enter name of music:\n");
    if (fgets(newMusic->name, LEN, stdin) == NULL) {
        result = SUCCESS;
    }
    printf("Enter name of music artist:\n");
    if (fgets(newMusic->artist, LEN, stdin) == NULL) {
        result = SUCCESS;
    }
    printf("Enter duration of music:\n");
    if (!scanf("%d", &newMusic->duration) || newMusic->duration > MIN_DURATION || newMusic->duration < MAX_DURATION) {
        result = SUCCESS;
    }
    printf("Enter music rank by your oppinion:\n");
    if (!scanf("%d", &newMusic->rank) || newMusic->rank > MIN_RANK || newMusic->rank < MAX_RANK) {
        result = SUCCESS;
    }

    return result;
}


void addNewMusic(const char* filePath) {
    puts("");
    Music newMusic;

    if (readMusic(&newMusic)){
        addReadedMusic(filePath, &newMusic);
    } else {
        printf("Incorrect input");
    }
}


void addReadedMusic(const char* filePath, Music* newMusic) {
    FILE* catalog = openFile(filePath, "a+b");
    if (catalog) {
        fwrite(newMusic, sizeof(Music), 1, catalog);

        closeFile(catalog);
        printf("\nMusic added\n\n");
    } else {
        printf("Error opening the file");
    }
}


void showMusic(const char* filePath) {
    puts("");
    FILE* catalog = openFile(filePath, "rb");

    if (catalog) {
        Music readMusic;

        while ((fread(&readMusic, sizeof(Music), 1, catalog)) != 0) {       //reading another Music
            printMusic(readMusic);
        }
    } else {
        printf("Error opening the file");
    }

    closeFile(catalog);
}

void sortMusicRankName(FILE* catalog, int sizeOfList, int(*cmp)(Music*, Music*)) {
    Music readMusic1, readMusic2;

    for (int i = 0; i < sizeOfList - 1; i++) {
        for (int j = i + 1; j < sizeOfList; j++) {
            readMusicFromFile(catalog, &readMusic1, i);
            readMusicFromFile(catalog, &readMusic2, j);
            if (cmp(&readMusic1, &readMusic2) > 0) {
                swap(catalog, i, j);
            }
        }
    }
}

int compareByRank(Music* readMusic1, Music* readMusic2) {
    return readMusic1->rank > readMusic2->rank;
}

int compareByName(Music* readMusic1, Music* readMusic2) {
    return readMusic1->rank == readMusic2->rank && myStrcmp(readMusic1->name, readMusic2->name) > 0;
}


void sortMusicByRankAndName(const char* filePath) {
    int countOfMusic = countCheck(filePath);
    FILE* catalog = openFile(filePath, "r+b");

    if (catalog) {
        sortMusicRankName(catalog, countOfMusic, compareByRank);
        sortMusicRankName(catalog, countOfMusic, compareByName);
        printf("\nMusic list sorted!\n\n");
    } else {
        printf("Error opening the file");
    }

    closeFile(catalog);
}



int deleteMusic(FILE* catalog, int countOfMusic, const char artistToDelete[LEN], const char* filePath) {
    int countOfDeletedElements = 0;
    Music readMusic;
    for (int i = countOfMusic - 1; i >= 0; i--) {
        fseek(catalog, i * sizeof(Music), SEEK_SET);
        fread(&readMusic, sizeof(Music), 1, catalog);

        if (myStrcmp(readMusic.artist, artistToDelete) == 0) {
            for (int j = i; j < countOfMusic - 1; j++) {
                fseek(catalog, (j + 1) * sizeof(Music), SEEK_SET);
                fread(&readMusic, sizeof(Music), 1, catalog);

                fseek(catalog, j * sizeof(Music), SEEK_SET);
                fwrite(&readMusic, sizeof(Music), 1, catalog);
            }
            fseek(catalog, (-1) * sizeof(Music), SEEK_END);
            countOfMusic--;
            truncate(filePath, countOfMusic * sizeof(Music));
            countOfDeletedElements++;
        }
    }

    return countOfDeletedElements;
}


void deleteMusicByArtist(const char* filePath) {
    puts("");
    int countOfMusic = countCheck(filePath);
    char artistToDelete[LEN];

    FILE* catalog = openFile(filePath, "r+b");

    if (catalog) {
        printf("Enter name of artist which music you want to delete:\n");
        fgets(artistToDelete, LEN, stdin);
        if (!deleteMusic(catalog, countOfMusic, artistToDelete, filePath)) {
            printf("There's no music of this artist\n");
        } else {
            printf("\nMusic are deleted\n\n");
        }
    } else {
        printf("Error opening the file\n");
    }
    closeFile(catalog);
}

void executeSelectedCommand(const char* filePath, int mode) {
    switch (mode) {
    case ADD:
        addNewMusic(filePath);
        break;
    case SHOW:
        showMusic(filePath);
        break;
    case SORT:
        sortMusicByRankAndName(filePath);
        break;
    case DELETE:
        deleteMusicByArtist(filePath);
        break;
    default:
        printf("You entered wrong symbol. Please, enter symbol 1-5\n");
        break;
    }
}
