#include <stdio.h>
#include <malloc.h>

#define ERROR -1
#define SUCCESS 0

#define COUNT_OF_SIZE 1
#define COUNT_OF_NUMBERS 1

int inputArray(int* arr, int n);
void swap(int* elem1, int* elem2);
void sortArray(int* arr, int n);
void groupZero(int* arr, int n);
void groupPositive(int* arr, int n);
void printArray(int* arr, int n);
int inputSize(int *n);
int* allocMemory(int n);
void dellocMemory(int* arr);


int main() {
    int size;
    int *arr;
    if (inputSize(&size) == ERROR) {
        printf("Incorrect input\n");
    } else {
        arr = allocMemory(size);
        if (arr == NULL) {
            printf("Incorrect input\n");
        } else if (inputArray(arr, size) == ERROR) {
            printf("Incorrect input\n");
        } else {
            sortArray(arr, size);
            groupZero(arr, size);
            groupPositive(arr, size);
            printArray(arr, size);
        }
        if (arr != NULL) {
            dellocMemory(arr);
        }
    }

}

int inputArray(int* arr, int n) {
    int result = SUCCESS;
    if (n > 0) {
        printf("Enter array: \n");

    }
    for (int i = 0; i < n; i++) {
        int countOfNumbers = scanf("%d", arr + i);
        if (countOfNumbers != COUNT_OF_NUMBERS) {
            result = ERROR;
        }
    }
    return result;
}

void swap(int* elem1, int* elem2) {
    int temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
}

void sortArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) >= *(arr + j + 1)) {
                swap(arr + j, arr + j + 1);
            }
        }

    }
}

void groupZero(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) < 0 && !*(arr + j + 1)) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

void groupPositive(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) < 0 && *(arr + j + 1) > 0) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int inputSize(int *n) {
    int result = SUCCESS;
    printf("Enter size of array: \n");
    int countOfSize = scanf("%d", n);
    if (countOfSize != COUNT_OF_SIZE || *n < 0) {
        result = ERROR;
    }
    return result;
}

int* allocMemory(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    return arr;
}

void dellocMemory(int* arr) {
    free(arr);
}
