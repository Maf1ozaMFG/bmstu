#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

Music* allocMemory() {
    return (Music*)calloc(1, sizeof(Music));
}

Music* reallocMemory(Music* musicList, const int countOfSongs) {
    return (Music*)realloc(musicList, countOfSongs * sizeof(Music));
}

void freeMemory(Music* musicList) {
    free(musicList);
}

void swap(Music* a, Music* b) {
    Music temp = *a;
    *a = *b;
    *b = temp;
}
