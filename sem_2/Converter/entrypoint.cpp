#include "entrypoint.h"
#include "mymalloc.h"
#include "logic.h"

void doOperation(AppParams* params, AppContext* context, int operation) {
    switch(operation) {
        case VALIDATE:
            doValidation(params, context);
            break;
        case CONVERT:
            doConverting(params, context);
            break;
        case CLEAR:
            doClear(context);
            break;
        case INITCON:
            allocContext(context);
            break;
        case DEINITCON:
            freeContext(context);
            break;
        case INITPARAM:
            allocParams(params);
            break;
        case DEINITPARAM:
            freeParams(params);
            break;
        default:
            break;
    }
}


