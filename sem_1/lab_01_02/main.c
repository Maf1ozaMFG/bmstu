#include <stdio.h>
#include <math.h>
#define EPS 0.000001

#define POINT_ON_1_3 13
#define POINT_ON_2_3 23
#define POINT_ON_1_2 12
#define POINT_ON_1 1
#define POINT_ON_2 2
#define POINT_ON_3 3
#define POINT_IN_REGION_1 11
#define POINT_IN_REGION_2 22
#define POINT_IN_REGION_3 33
#define POINT_IN_REGION_4 44
#define POINT_IN_REGION_5 55
#define POINT_IN_REGION_6 66
#define POINT_IN_REGION_7 77

#define COUNT_OF_COORDINATES 2


#define SUCCESS 0
#define ERROR 1

float calculatingFunction1(float x){
    return 2 * x + 2;
}
float calculatingFunction2(float x){
    return 0.5 * x - 1;
}
float calculatingFunction3(float x){
    return - x + 2;
}
int input(float *x, float *y){
    int a;
    printf("Line equations:\ny=2x+2\ny=0,5x-1\ny=-x+2\nEnter point coordinates:\n");
    a = scanf("%f %f", x, y);
    return a;
}
int checkLines(float x, float y){
    float function1, function2, function3;
    function1 = calculatingFunction1(x);
    function2 = calculatingFunction2(x);
    function3 = calculatingFunction3(x);
    if (fabs(y - function1) < EPS && fabs(y - function2) < EPS){
        return POINT_ON_1_2;
    } else if (fabs(y - function1) < EPS && fabs(y - function3) < EPS){
        return POINT_ON_1_3;
    } else if (fabs(y - function3) < EPS && fabs(y - function2) < EPS){
        return POINT_ON_2_3;
    } else if (fabs(y - function1) < EPS){
        return POINT_ON_1;
    } else if (fabs(y - function3) < EPS){
        return POINT_ON_3;
    } else if (fabs(y - function2) < EPS){
        return POINT_ON_2;
    }
    return SUCCESS;
}
int checkRegions(float x, float y){
    float function1, function2, function3;
    function1 = calculatingFunction1(x);
    function2 = calculatingFunction2(x);
    function3 = calculatingFunction3(x);
    if ((y < function1) && (y > function2) && (y > function3)){
        return POINT_IN_REGION_1;
    } else if ((y < function1) && (y < function2) && (y > function3)){
        return POINT_IN_REGION_2;
    } else if ((y < function1) && (y < function2) && (y < function3)){
        return POINT_IN_REGION_3;
    } else if ((y > function1) && (y < function2) && (y < function3)){
        return POINT_IN_REGION_4;
    } else if ((y > function1) && (y > function2) && (y < function3)){
        return POINT_IN_REGION_5;
    } else if ((y > function1) && (y > function2) && (y > function3)){
        return POINT_IN_REGION_6;
    } else if ((y < function1) && (y > function2) && (y < function3)){
        return POINT_IN_REGION_7;
    }
    return SUCCESS;
}
void outputLines(int n){
    switch(n){
        case POINT_ON_1_3:
            printf("Point placed on lines 1 and 3");
            break;
        case POINT_ON_1_2:
            printf("Point placed on lines 1 and 2");
            break;
        case POINT_ON_2_3:
            printf("Point placed on lines 2 and 3");
            break;
        case POINT_ON_1:
            printf("Point placed on line 1");
            break;
        case POINT_ON_2:
            printf("Point placed on line 2");
            break;
        case POINT_ON_3:
            printf("Point placed on line 3");
            break;
    }
}
void outputRegions (int n){
    switch(n){
        case POINT_IN_REGION_1:
            printf("Point placed in region 1");
            break;
        case POINT_IN_REGION_2:
            printf("Point placed in region 2");
            break;
        case POINT_IN_REGION_3:
            printf("Point placed in region 3");
            break;
        case POINT_IN_REGION_4:
            printf("Point placed in region 4");
            break;
        case POINT_IN_REGION_5:
            printf("Point placed in region 5");
            break;
        case POINT_IN_REGION_6:
            printf("Point placed in region 6");
            break;
        case POINT_IN_REGION_7:
            printf("Point placed in region 7");
            break;
    }
}
int main(){
    float x, y;
    int a;
    a = input(&x, &y);
    if (a != COUNT_OF_COORDINATES){
        printf("Result: Incorrect input");
        return ERROR;
    } else {
        printf("Result: ");
        a = checkLines(x, y);
        outputLines(a);
        a = checkRegions(x, y);
        outputRegions(a);
    }
    return SUCCESS;
}
