#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

#define BIN "2"
#define DEC "10"
#define HEX "16" 

enum BORDERS_OF_RADIX {
    MINRADIX = 2,
    MAXRADIX = 16
};

typedef struct {
    std::string radixFrom;
    std::string radixTo;

    std::string initValue;

    int signOfNumber;
    int validationResult;
} AppParams;


void checkAvailabilityOfRadix(AppParams* params, AppContext* context);
void radixValidation(AppParams* params, AppContext* context);

void checkAvailabilityOfNumber(AppParams* params, AppContext* context);
void numberValidation(AppParams* params, AppContext* context);

void validation(AppParams* params, AppContext* context);

void doOperationConverting(AppParams* params, AppContext* context);
void doOperationClear(AppContext* context);

#endif // ENTRYPOINT_H
