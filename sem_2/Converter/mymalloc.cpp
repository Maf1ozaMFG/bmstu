#include "mymalloc.h"

void allocParams(AppParams* params) {
    params->radixFrom = (char*)calloc(SIZE, sizeof(char));
    params->radixTo = (char*)calloc(SIZE, sizeof(char));
    params->initValue = (char*)calloc(SIZE, sizeof(char));

}


void freeParams(AppParams* params) {
    free(params->radixFrom);
    free(params->radixTo);
    free(params->initValue);
}


void allocContext(AppContext* context) {
    context->resultValue = (char*)calloc(SIZE, sizeof(char));
    context->validationState = (char*)calloc(SIZE, sizeof(char));
}


void freeContext(AppContext* context) {
    free(context->resultValue);
    free(context->validationState);
}
