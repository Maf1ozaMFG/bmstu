#ifndef MENUMETHODS_H
#define MENUMETHODS_H

#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

enum {
    ERROR = 0,
    SUCCESS,
    ADD = 1,
    SHOW,
    SORT,
    DELETE,
    EXIT
};

int readMusic(Music* newMusic);

void addReadMusic(const char* filePath, Music newMusic);
void addMusic(const char* filePath);

void printMusic(Music readMusic);
void printMusicList(Music* musicArr, const int countOfMusic);
void showAllMusic(const char* filePath);

void sortMusic(Music* musicArr, const int sizeOfArr, int(*cmp)(Music*, Music*));
void sortMusicByName(const char* filePath);
int compare(Music* a, Music* b);

int deleteMusic(Music* musicArr, int* countOfMusic, const char artist[LEN]);
void deleteMusicByArtist(const char* filePath);

void executeSelectedMode(const char* filePath, int mode);


#endif // MENUMETHODS_H
