#include "mystring.h"
#include "menumethods.h"
#include "infomethods.h"

void printMusic(Music readMusic) {
    printf("Music name: %s", readMusic.name);
    printf("Music artist: %s", readMusic.artist);
    printf("Music duration: %d\n", readMusic.duration);
    printf("Music rank: %d\n", readMusic.rank);
    printf("\n");
}

void printMusicList(Music* musicArr, const int countOfMusic) {
    printf("Music list:\n\n");
    for (int i = 0; i < countOfMusic; i++) {
        printMusic(*(musicArr + i));
    }
}

int readMusic(Music* newMusic) {
    int result = SUCCESS;

    printf("Enter name of music:\n  ");
    if (fgets(newMusic->name, LEN, stdin) == NULL || newMusic->name[0] == '\n' ||  newMusic->name[0] == '\0') {
        result = ERROR;
    }
    printf("Enter name of artist:\n  ");
    if (fgets(newMusic->artist, LEN, stdin) == NULL || newMusic->artist[0] == '\n' ||  newMusic->artist[0] == '\0') {
        result = ERROR;
    }
    printf("Enter music duration:\n  ");
    if (!scanf("%d", &newMusic->duration)) {
        result = ERROR;
    }
    printf("Enter rank of music by your opinion:\n  ");
    if (!scanf("%d", &newMusic->rank)) {
        result = ERROR;
    }

    return result;
}

void addReadMusic(const char* filePath, Music newMusic) {
    FILE* catalog = openFile(filePath, "a+");
    if (catalog) {
        fputs(newMusic.name, catalog);
        fputs(newMusic.artist, catalog);
        fprintf(catalog, "%d\n", newMusic.duration);
        fprintf(catalog, "%d\n", newMusic.rank);
    } else {
        printf("Error: File is unreadable\n");
    }

    closeFile(catalog);

    printf("Music added into catalog!\n");
}

void addMusic(const char* filePath) {
    printf("\n");
    Music newMusic;
    if (readMusic(&newMusic)) {
        addReadMusic(filePath, newMusic);
    } else {
        printf("Error: Incorrect input\n");
    }
}

void showAllMusic(const char* filePath) {
    printf("\n");
    int countOfMusic = 0;

    Music* musicArr = readInfo(filePath, &countOfMusic);
    if (musicArr != NULL) {
        printMusicList(musicArr, countOfMusic);
    }

    freeMemory(musicArr);
}

void sortMusic(Music* musicArr, const int sizeOfArr, int(*cmp)(Music*, Music*)) {
    for (int i = 0; i < sizeOfArr - 1; i++) {
        for (int j = i + 1; j < sizeOfArr; j++) {
            if(cmp(musicArr + i, musicArr + j) > 0) {
                swap(musicArr + i, musicArr + j);
            }
        }
    }
}

int compare(Music* a, Music* b) {
    return myStrcmp(a->name, b->name);
}

void sortMusicByName(const char* filePath) {
    printf("\n");
    int countOfMusic = 0;

    Music* musicArr = readInfo(filePath, &countOfMusic);

    if (musicArr != NULL) {
        sortMusic(musicArr, countOfMusic, compare);

        printf("\nSorted music by name\n");
        printMusicList(musicArr, countOfMusic);

        saveInfo(filePath, musicArr, countOfMusic);
    }

    freeMemory(musicArr);
}

int deleteMusic(Music* musicArr, int* countOfMusic, const char artist[LEN]) {
    int countOfDeletedElems = 0;
    for (int i = *countOfMusic; i >= 0; i--) {
        if (!myStrcmp(musicArr[i].artist, artist)) {
            for (int j = i; j < *countOfMusic - 1; j++) {
                *(musicArr + j) = *(musicArr + j + 1);
            }
            *countOfMusic = *countOfMusic - 1;
            countOfDeletedElems++;
        }
    }
    return countOfDeletedElems;
}

void deleteMusicByArtist(const char* filePath) {
    printf("\n");
    int countOfMusic = 0;
    char artist[LEN];

    Music* musicArr = readInfo(filePath, &countOfMusic);

    if (musicArr != NULL) {
        printf("Enter artist which music you want to delete:\n");
        fgets(artist, LEN, stdin);
        if (!deleteMusic(musicArr, &countOfMusic, artist)) {
            printf("Music by this artist does not exist\n");
            saveInfo(filePath, musicArr, countOfMusic);
        } else {
            printf("\nMusic are deleted\n");
            saveInfo(filePath, musicArr, countOfMusic);
        }
        printMusicList(musicArr, countOfMusic);
    }
    freeMemory(musicArr);
}

void executeSelectedMode(const char* filePath, int mode) {
    switch (mode) {
    case ADD:
        addMusic(filePath);
        break;
    case SHOW:
        showAllMusic(filePath);
        break;
    case SORT:
        sortMusicByName(filePath);
        break;
    case DELETE:
        deleteMusicByArtist(filePath);
        break;
    default:
        printf("You entered wrong symbol. Please, enter symbols 1-5\n");
        break;

    }
}
