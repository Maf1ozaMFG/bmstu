#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

#define BIN "2"
#define DEC "10"
#define HEX "16"

enum OPERATION {
    VALIDATE = 1,
    CONVERT,
    CLEAR,
    INITCON,
    DEINITCON,
    INITPARAM,
    DEINITPARAM,
};

enum BORDERS_OF_RADIX {
    MINRADIX = 2,
    MAXRADIX = 36
};

typedef struct {
    char* radixFrom;
    char* radixTo;
    char* initValue;
    int validationState;
} AppParams;

void doOperation(AppParams* params, AppContext* context, int operation);


#endif // ENTRYPOINT_H
