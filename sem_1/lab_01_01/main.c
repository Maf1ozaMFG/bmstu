#include <stdio.h>
#define EPS 0.000001

#define POINT_IS_ABOVE_THE_LINE 1
#define POINT_IS_UNDER_THE_LINE -1
#define POINT_IS_ON_LINE 0

#define COUNT_OF_COORDINATES 2

#define SUCCESS 0

float calculatingFunction(float x){
    return 0.5 * x + 1;
}


int input(float *x, float *y){
    int a;
    printf("Line equation:= y = 0.5x + 1\nEnter point coordinates:\n");
    a = scanf("%f %f", x, y);
    return a;
}
int finder(float x, float y){
    float function;
    function = calculatingFunction(x);
    if (function > y + EPS){
     return POINT_IS_UNDER_THE_LINE;
    }
    else if (function < y - EPS){
     return POINT_IS_ABOVE_THE_LINE;
    } else {
     return POINT_IS_ON_LINE; 
    }
}
void output(int n){
    switch(n) {
        case POINT_IS_ABOVE_THE_LINE:
            printf("Result: Point is above the line");
            break;
        case POINT_IS_UNDER_THE_LINE:
            printf("Result: Point is under the line");
            break;
        case POINT_IS_ON_LINE:
            printf("Result: Point is on the line");
        break; 
    }
}
int main(){
    float x, y;
    int a;
    a = input(&x, &y);
    if (a != COUNT_OF_COORDINATES){
        printf("Result: Incorrect input");
    } else {
        a = finder(x, y);
        output(a);
    }
    return SUCCESS;
}
