#include "entrypoint.h"



void checkAvailabilityOfRadix(AppParams* params, AppContext* context) {
    if (params->radixFrom == "") {
        context->validationResult = "Error: select radix from";
        params->validationResult = ERROR;
    } else if (params->radixTo == "") {
        context->validationResult = "Error: select radix to";
        params->validationResult = ERROR;
    }
}

void radixValidation(AppParams* params, AppContext* context) {
    char digits[] = "0123456789";
    checkAvailabilityOfRadix(params, context);
    if (params->validationResult) {
        for (int i = 0; i < (int)params->radixTo.length(); i++) {
            char* sym = std::strchr(digits, params->radixFrom[i]);
            if (sym == NULL) {
                context->validationResult = "Error: incorrect radix from";
                params->validationResult = ERROR;
                break;
            }
        }
        for (int i = 0; i < (int)params->radixTo.length(); i++) {
            char* sym = std::strchr(digits, params->radixTo[i]);
            if (sym == NULL) {
                context->validationResult = "Error: incorrect radix to";
                params->validationResult = ERROR;
                break;
            }
        }
    }
    if (params->validationResult) {
        int radixFrom = std::stoi(params->radixFrom);
        int radixTo = std::stoi(params->radixTo);

        if (radixFrom < MINRADIX || radixFrom > MAXRADIX || radixTo < MINRADIX || radixTo > MAXRADIX) {     //check availability of radix
            context->validationResult = "Error: radix have to be from 2 to 16 range";
            params->validationResult = ERROR;
        }
    }
}

void checkAvailabilityOfNumber(AppParams* params, AppContext* context) {
    if (params->initValue == "") {
        params->validationResult = ERROR;
        context->validationResult = "Enter: you have to enter some number to convert";
    }
}

void numberValidation(AppParams* params, AppContext* context) {
    checkAvailabilityOfNumber(params, context);
    if (params->validationResult) {
        int radixFrom = std::stoi(params->radixFrom);
        char existingRadixes[] = "0123456789abcdefABCDEF";
        for (int i = 0; i < (int)params->initValue.length(); i++) {
            char* sym = std::strchr(existingRadixes, params->initValue[i]);
            if (sym - existingRadixes > radixFrom - 1 || sym == NULL) {
                params->validationResult = ERROR;
                context->validationResult = "Error: you're entered incorrect number";
                break;
            }
        }
    }
}

void validation(AppParams* params, AppContext* context) {
    radixValidation(params, context);
    numberValidation(params, context);
}

void doOperationConverting(AppParams* params, AppContext* context) {
    int radixFrom = std::stoi(params->radixFrom);
    int radixTo = std::stoi(params->radixTo);
    if (params->validationResult) {
        doConvert(context, params->initValue, radixFrom, radixTo, params->signOfNumber);
    }
}

void doOperationClear(AppContext* context) {
    context->resultValue = "";
}

