#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SUCCESS 0
#define ERROR -1

#define NECESSARY_COUNT_OF_SIZE 1
#define NECCESARY_COUNT_OF_ELEMENT 1

int inputSize(int* size);
int inputArray(int* arr, int n);
int findIndexMax(int* arr, int n);
int findSum(int* arr, int n, int indexMax, int max);
int* allocMemory(int n);
void deallocMemory(int* arr);
void printSum(int sum);

int main() {
    int* arr;
    int size;
    if (inputSize(&size) == ERROR) {
        printf("Incorrect input\n");
    } else {
        arr = allocMemory(size);
        if (arr == NULL) {
            printf("Incorrect input\n");

        } else if (inputArray(arr, size) == ERROR) {
            printf("Incorrect input\n");
        } else {
            int indexMax = findIndexMax(arr, size);
            int max = *(arr + indexMax);
            int sum = findSum(arr, size, indexMax, max);
            printSum(sum);
            }
        if (arr != NULL) {
            deallocMemory(arr);
        }
    }
}


int inputSize(int* size) {
    int result = SUCCESS;
    printf("Enter size of array: \n");
    int countOfSize = scanf("%d", size);
    if (countOfSize != NECESSARY_COUNT_OF_SIZE || *size <= 0) {
        result = ERROR;
    }
    return result;
}

int inputArray(int* arr, int n) {
    int result = SUCCESS;
    printf("Enter array: \n");
    for (int i = 0; i < n; i++) {
        int countOfNumbers = scanf("%d", arr + i);
        if (countOfNumbers != NECCESARY_COUNT_OF_ELEMENT) {
            result = ERROR;
        }
    }
    return result;

}

int findIndexMax(int* arr, int n) {
    int indexMax = 0;
    for (int i = 1; i < n; i++) {
        if (*(arr + indexMax) < *(arr + i)) {
            indexMax = i;
        }
    }
    return indexMax;
}

int findSum(int* arr, int n, int indexMax, int max) {
    int sum = 0;
    for (int i = indexMax + 2; i < n; i += 2) {
        if (*(arr + i) > max / 2) {
            sum += *(arr + i);
        }
    }
    return sum;
}

int* allocMemory(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    return arr;
}

void deallocMemory(int* arr) {
    free(arr);
}

void printSum(int sum) {
        printf("%d\n", sum);
}
