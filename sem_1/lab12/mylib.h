#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define LEN 255

enum {
    ERROR = 0,
    SUCCESS,
    MAX_DURATION = 15,
    MIN_DURATION = 1,
    MAX_RANK = 10,
    MIN_RANK = 1,
    ADD = 1,
    SHOW,
    SORT,
    DELETE,
    EXIT

};

typedef struct {
    char name[LEN];
    char artist[LEN];
    int duration;
    int rank;

} Music;

int readMusicFromFile(FILE* catalog, Music* readMusic, int step);
void writeMusicToFile(FILE* catalog, Music* readMusic, int step);

void printInvitation();
int getCommand();
void executeSelectedCommand(const char* filePath, int mode);

char* getFilePath();
FILE* openFile(const char* filePath, char* mode);
void closeFile(FILE* catalog);

void swap(FILE* catalog, int a, int b);
int countCheck(const char* filePath);

int readMusic(Music* newMusic);
void addNewMusic(const char* filePath);
void addReadedMusic(const char* filePath, Music* newMusic);

void showMusic(const char* filePath);
void printMusic(Music readMusic);

void sortMusicRankName(FILE* catalog, int sizeOfList, int(*cmp)(Music*, Music*));
void sortMusicByRankAndName(const char* filePath);

int compareByRank(Music* readMusic1, Music* readMusic2);
int compareByName(Music* readMusic1, Music* readMusic2);

int deleteMusic(FILE* catalog, int countOfMusic, const char artistToDelete[LEN], const char* filePath);
void deleteMusicByArtist(const char* filePath);

#endif // MYLIB_H
