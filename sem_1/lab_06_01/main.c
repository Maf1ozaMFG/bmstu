#include <stdio.h>
#include <malloc.h>

#define SUCCESS 0
#define ERROR -1

#define COUNT_OF_SIZE 1
#define COUNT_OF_ELEMS 1

int** allocMatrix(int n);
void dellocMatrix(int** mat, int n);

int inputSquareMatrixSize(int* n);
int inputMatrix(int** mat, int n);
void printMatrix(int** mat, int n);

void swap(int* elem1, int* elem2);

void transpose(int** mat, int n);



int main() {
    int size;
    int** mat;
    if (inputSquareMatrixSize(&size) == ERROR) {
        printf("Incorrect input\n");
    } else if (size != 0) {
        mat = allocMatrix(size);
        if (mat == NULL) {
            printf("Incorrect input\n");
        } else if (inputMatrix(mat, size) == ERROR) {
            printf("Incorrect input\n");
        } else {
            transpose(mat, size);
            printMatrix(mat, size);
        }
        if (mat != NULL) {
            dellocMatrix(mat, size);
        }
    }
}

int** allocMatrix(int n) {
    int** mat = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        *(mat + i) =(int*)calloc(n, sizeof(int));
    }
    return mat;

}

void dellocMatrix(int** mat, int n) {
   for (int i = 0; i < n; i++) {
        free(*(mat + i));  
   }
   free(mat);
}

int inputSquareMatrixSize(int* n) {
    int result = ERROR;
    printf("Enter size of square matrix: \n");
    int countOfSize = scanf("%d", n);
    if (countOfSize == COUNT_OF_SIZE) {
        result = SUCCESS;
        if (*n < 0) {
            result = ERROR;
        }
    }
    return result;

}

int inputMatrix(int** mat, int n) {
    int result = SUCCESS;
    printf("Enter matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int countOfElems = scanf("%d", *(mat + i) + j);
            if (countOfElems != COUNT_OF_ELEMS) {
                result = ERROR;
            }
        }
    }
    return result;
}

void printMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

void transpose(int** mat, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            swap(*(mat + i) + j, *(mat + n - 1 - j) + n - 1 - i);
        }
    }
}

void swap(int* elem1, int* elem2) {
    int temp = *elem1;
    *elem1 = *elem2;
    *elem2 = temp;
}
