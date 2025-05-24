#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

#define ERR -1
#define FALSE '!'
#define INCORRECT "Incorrect input"

enum SUCCESSFUL {
    ERROR,
    SUCCESS
};

enum Digits {
    A = 10,
    F = 16
};


char intToChar(unsigned int digit);
unsigned int charToInt(char sym);

std::string toReverseCode(std::string number, int radix);
std::string fromReverseCode(std::string number, int radix);

std::string toExtraCode(std::string number, int radix);
std::string fromExtraCode(std::string number, int radix);

int convertToDecimalNumber(std::string number, int radix);
std::string convertToOtherRadix(int decimalNumber, int radix);

void doConvert(AppContext* context, std::string dataFromLineEdit, int radixFrom, int radixTo, int signOfValue);
void doClear(AppContext* context);

#endif // LOGIC_H
