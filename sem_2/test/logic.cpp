#include "logic.h"

unsigned int charToInt(char sym) {
    return (sym >= '0' && sym <= '9') ? (sym - '0') : (sym >= 'A' && sym <= 'F') ? (sym - 'A' + 10) : ERR;
}


char intToChar(unsigned int digit) {
    return (digit >= 0 && digit <= 9) ? ('0' + digit) : (digit >= A && digit <= F) ? ('A' + digit - 10) : '!';
}

std::string intToString(std::string string, int digit) {

    if (digit >= 0 && digit <= 9) {
        string += '0' + digit;
    } else if (digit >= A && digit <= F) {
        string += 'A' + digit - 10;
    } else {
        string += FALSE;
    }
    return string;
}

int stringToInt(char sym, int digit) {
    if (sym >= '0' && sym <= '9') {
        digit = sym - '0';
    } else if (sym >= 'A' && sym <= 'F') {
        digit = sym - 'A' + 10;
    } else if (sym >= 'a' && sym <= 'f') {
        digit = sym - 'a' + 10;
    } else {
        digit = -1;
    }

    return digit;
}

int convertToDecimalNumber(std::string number, int radix) {
    int decimalNumber = 0;
    int digit = 0;

    for (int i = (int)number.length() - 1; i >= 0; i--) {
        digit = stringToInt(number[i], digit);
        if (INT_MAX - decimalNumber >= digit * pow(radix, (int)number.length() - 1 - i)) {
            decimalNumber += digit * pow(radix, (int)number.length() - i - 1);
        } else {
            decimalNumber = 0;
            break;
        }
    }

    return decimalNumber;
}

std::string convertToOtherRadix(int decimalNumber, int radix) {
    std::string result;
    while (decimalNumber) {
        int remainderOfDivision = decimalNumber % radix;
        result = intToString(result, remainderOfDivision);
        decimalNumber /= radix;
    }
    std::reverse(result.begin(), result.end());

    return result;
}

int checkZero(std::string number) {
    int result = SUCCESS;

    for (int i = 0; i < (int)number.length(); i++) {
        if (number[i] != '0') {
            result = ERROR;
            break;
        }
    }

    return result;
}

void doConvert(AppContext* context, std::string dataFromLineEdit, int radixFrom, int radixTo, int signOfValue) {
    std::string result;

    if (checkZero(dataFromLineEdit)) {
        result = "0";
    } else if (radixFrom == radixTo) {
        result = dataFromLineEdit;
    } else {
        if (signOfValue > 0) {
            int decimalNumber;
            decimalNumber = convertToDecimalNumber(dataFromLineEdit, radixFrom);
            result = convertToOtherRadix(decimalNumber, radixTo);
        } else {
            result = transformNegNumber(dataFromLineEdit, radixFrom, radixTo);
        }
    }
    context->resultValue = result;
}

