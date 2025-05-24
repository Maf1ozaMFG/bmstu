#include <stdio.h>
#include <malloc.h>


#define SUCCESS 0
#define ERROR -1

#define COUNT_OF_SIZE 2
#define COUNT_OF_ELEMS 1

void transform(int** mat, int* vector, int n, int m);
int** allocMatrix(int n, int m);
void dellocMatrix(int** mat);

int inputMatrixSize(int* n, int* m);
int inputMatrix(int** mat, int n, int m);
void printMatrix(int** mat, int n, int m);

void sortMatrix(int** mat, int n, int m);
void reverseRows(int** mat, int n, int m);
void swap(int* elem1, int* elem2);



int main() {
    int rows;
    int cols;
    int** mat = NULL;
    if (inputMatrixSize(&rows, &cols) == ERROR) {
        printf("Incorrect input\n");
    } else {
        mat = allocMatrix(rows, cols);
        if (mat != NULL) {
            if (inputMatrix(mat, rows, cols) == ERROR) {
                printf("Incorrect input\n");
            } else {
                sortMatrix(mat, rows, cols);
                reverseRows(mat, rows, cols);
                printMatrix(mat, rows, cols);
            }
            dellocMatrix(mat);
        } else {
            printf("Incorrect input\n");
        }
    }
}

int** allocMatrix(int n, int m) {
    int* vector = NULL;
    int** mat = (int**)calloc(n, sizeof(int*));
    if (mat != NULL) {
        vector = (int*)calloc(n * m, sizeof(int));
        if (vector == NULL) {
            free(mat);
        }
    }
    transform(mat, vector, n, m);
    return mat;

}

void dellocMatrix(int** mat) {
    free(*mat);
    free(mat);
}

void transform(int** mat, int* vector, int n, int m) {
    for (int i = 0; i < n; i++) {
        *(mat + i) = vector + i * m;
    }
}

int inputMatrixSize(int* n, int* m) {
    int result = ERROR;
    if (n == NULL || m == NULL) {
        return result;
    }
    printf("Enter size of matrix: \n");
    int countOfSize = scanf("%d %d", n, m);
    if (countOfSize == COUNT_OF_SIZE && *n > 0 && *m > 0) {
        result = SUCCESS;
    }
    return result;

}

int inputMatrix(int** mat, int n, int m) {
    int result = SUCCESS;
    printf("Enter matrix: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int countOfElems = scanf("%d", *(mat + i) + j);
            if (countOfElems != COUNT_OF_ELEMS) {
                result = ERROR;
            }
        }
    }
    return result;
}

void printMatrix(int** mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

void swap(int* elem1, int* elem2) {
    int temp = *elem2;
    *elem2 = *elem1;
    *elem1 = temp;
}

void sortMatrix(int** mat, int n, int m) {
    int* vector = *mat;
    int size = n * m;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (*(vector + i) >= *(vector + j)) {
                swap(vector + i, vector + j);
            }
        }
    }
}

void reverseRows(int** mat, int n, int m) {
    for (int i = 1; i < n; i += 2) {
        for (int j = 0; j < m / 2; j++) {
            swap(*(mat + i) + j, *(mat + i) + m - j - 1);
        }
    }
}
