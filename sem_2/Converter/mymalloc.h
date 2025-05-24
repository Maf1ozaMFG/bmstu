#ifndef MYMALLOC_H
#define MYMALLOC_H

#include "entrypoint.h"
#define SIZE 255

void allocParams(AppParams* params);
void freeParams(AppParams* params);

void allocContext(AppContext* context);
void freeContext(AppContext* context);

#endif // MYMALLOC_H
