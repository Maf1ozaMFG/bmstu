#include <stdio.h>
#include <math.h>

#define SUCCESS 0
#define ERROR 1

#define COUNT_OF_EPS 1
#define EPS 1e-10

int readEps(double *eps);
double func(double previous, int k);
double calculatingSum(long double eps);




int main() {
    double eps;
    if (readEps(&eps) == SUCCESS) {
        double valueOfSum = calculatingSum(eps);
        printf("%.6lf\n", valueOfSum);
    } else {
        printf("Incorrect input\n");
    }

}

int readEps(double *eps) {
    int result = SUCCESS;
    int epsCheck = scanf("%lf", eps);
    if (epsCheck != COUNT_OF_EPS || *eps < EPS) {
        result = ERROR;
    }
    return result;

}

double func(double previous, int k) {
    return (-1) * previous / k;

}

double calculatingSum(long double eps) {
    double valueOfSum = 1;
    double term = 1;
    int i = 0;
    while (fabs(term) > eps) {
        i++;
        term = func(term, i);
        valueOfSum += term;
    }
    return valueOfSum;

}

