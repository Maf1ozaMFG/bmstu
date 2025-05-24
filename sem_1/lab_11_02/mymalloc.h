#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdio.h>
#include <stdlib.h>

#define LEN 255

typedef struct {
    char name[LEN];
    char artist[LEN];
    int duration;
    int rank;

} Music;

Music* allocMemory();
Music* reallocMemory(Music* musicList, const int countOfSongs);
void freeMemory(Music* musicList);
void swap(Music* a, Music* b);

#endif // MYMALLOC_H
