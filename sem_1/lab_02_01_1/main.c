#include <math.h>
#include <stdio.h>


#define ERR 1
#define SUCCESS 0

#define NECESSARY_COUNT_FOR_INTERVAL 2
#define NECESSARY_COUNT_FOR_ITERATIONS 1
#define NECESSARY_VALUE_OF_ITERATIONS 2

float calculating(float x);
float input(float *firstNumber, float *secondNumber, int *n);
void funcFor(float firstNumber, float secondNumber, int n);
void funcWhile(float firstNumber, float secondNumber, int n);
void funcDoWhile(float firstNumber, float secondNumber, int n);

int main() {
    float firstNumber, secondNumber;
    int n;
    if (input(&firstNumber, &secondNumber, &n) == SUCCESS) {
        funcFor(firstNumber, secondNumber, n);
        funcWhile(firstNumber, secondNumber, n);
        funcDoWhile(firstNumber, secondNumber, n);
    } else {
        printf("Incorrect input\n");
    }

}
float calculating(float x) {
    float result;
    if (x == 0) {
        result = NAN;
    } else {
        result = (sin(x) * sin(x)) / x;
    }
    return result;

}
float input(float *firstNumber, float *secondNumber, int *n) {
    int firstInput = SUCCESS;
    printf("Enter first and second numbers of interval:\n");
    int countOfInterval = scanf("%f %f", firstNumber, secondNumber);
    if (countOfInterval != NECESSARY_COUNT_FOR_INTERVAL || *secondNumber <= *firstNumber){
        firstInput = ERR;
    }
    int secondInput = SUCCESS;
    printf("Enter number of iterations:\n");
    int countOfIterations = scanf("%d", n);
    if (countOfIterations != NECESSARY_COUNT_FOR_ITERATIONS || *n < NECESSARY_VALUE_OF_ITERATIONS) {
        secondInput = ERR;
    }
    int result = SUCCESS;
    if (firstInput == ERR || secondInput == ERR) {
        result = ERR;
    }
    return result;

}
void funcFor(float firstNumber, float secondNumber, int n) {
    float step = (secondNumber - firstNumber) / (n - 1);
    float current = firstNumber;
    printf("for: \n");
    printf("x    |");

    for (int i = 0; i < n; i++) {
        printf("% -7.3f|", current);
        current += step;
    }
    current = firstNumber;
    printf("\nf(x) |");
    for (int i = 0; i < n; i++) {
        float result = calculating(current);
        if (isnan(result)) {
            printf("  nan  |");
        } else {
            printf("% -7.3f|", result);
        }
        current += step;
    }
    printf("\n\n");
}
void funcWhile(float firstNumber, float secondNumber, int n) {
    float step = (secondNumber - firstNumber) / (n - 1);
    float current = firstNumber;
    printf("while: \n");
    printf("x    |");
    while (current <= secondNumber){
        printf("% -7.3f|", current);
        current += step;
    }
    current = firstNumber;
    printf("\nf(x) |");
    while (current <= secondNumber){
        float result = calculating(current);
        if (isnan(result)) {
            printf("  nan  |");
        } else {
            printf("% -7.3f|", result);
        }
        current += step;
    }
    printf("\n\n");
}
void funcDoWhile(float firstNumber, float secondNumber, int n) {
    float step = (secondNumber - firstNumber) / (n - 1);
    float current = firstNumber;
    printf("do while: \n");
    printf("x    |");
    do {
        printf("% -7.3f|", current);
        current += step;
    } while (current <= secondNumber);
    current = firstNumber;
    printf("\nf(x) |");
    do {
        float result = calculating(current);
        if (isnan(result)) {
            printf("  nan  |");
        } else {
            printf("% -7.3f|", result);
        }
        current += step;
    } while (current <= secondNumber);
    printf("\n\n");
}
