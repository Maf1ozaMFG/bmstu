#include <stdio.h>
#include <math.h>

#define SUCCESS 0
#define ERROR -1

#define COUNT_OF_EPS 1
#define COUNT_OF_BORDERS 2
#define EPS 1e-10


double calculatingIntegral(double a, double b, double eps);
double function(double x);
int input(double *a, double *b, double *eps);

int main() {
     double a, b, eps;
     if (input(&a, &b, &eps) == SUCCESS) {
        double current = calculatingIntegral(a, b, eps);
        printf("%.6lf\n", current);
    } else {
        printf("Incorrect input\n");
    }

}

double function(double x) {
   return log(x);

}

int input(double *a, double *b, double *eps) {
    int result = SUCCESS;
    printf("Enter borders of integral and epsilon: \n");
    int bordersCount = scanf("%lf %lf", a, b);
    if (bordersCount != COUNT_OF_BORDERS || *a < EPS || *b < EPS) {
        result = ERROR;
    }
    int epsCheck = scanf("%lf", eps);
    if (epsCheck != COUNT_OF_EPS || *eps < EPS) {
        result = ERROR;
    }
    return result;

}

double calculatingIntegral(double a, double b, double eps) {
    int n = 1;
    double current, previous;
    double h = (b - a) / n;
    current = h * log((a + b) / 2);
    do {
        n *= 2;
        previous = current;
        current = 0;
        h = (b - a) / n;
        for (int i = 0; i < n; i++) {
            current += h * function(a + h * (i + 0.5));
        }
    } while (fabs(current - previous) > eps);
    return current;

}
