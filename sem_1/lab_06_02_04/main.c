#include <stdio.h>
#include <malloc.h>

#define SUCCESS 0
#define ERROR -1

#define NO_STRING_TO_DELETE -1

#define COUNT_OF_SIZE 2
#define COUNT_OF_ELEMS 1

void transform(int** mat, int* vector, int n, int m);
int** allocMatrix(int n, int m);
void dellocMatrix(int** mat);

int inputMatrixSize(int* n, int* m);
int inputMatrix(int** mat, int n, int m);
void printMatrix(int** mat, int n, int m);

int findLastMinElem(int** mat, int n, int m);
void deleteRowWithLastMin(int **mat, int row_with_min, int* n);



int main() {
    int rows;
    int cols;
    int** mat;
    if (inputMatrixSize(&rows, &cols) == ERROR) {
        printf("Incorrect input\n");
    } else if (rows != 0 && cols != 0) {
        mat = allocMatrix(rows, cols);
        if (mat == NULL) {
            printf("Incorrect input\n");
        } else if (inputMatrix(mat, rows, cols) == ERROR) {
            printf("Incorrect input\n");
        } else {
            int rowWithMin = findLastMinElem(mat, rows, cols);
            deleteRowWithLastMin(mat, rowWithMin, &rows);
            printMatrix(mat, rows, cols);
        }
        if (mat != NULL) {
            dellocMatrix(mat);
        }
    }
}


int** allocMatrix(int n, int m) {
    int** mat = (int**)calloc(n, sizeof(int*));
    int* vector = (int*)calloc(n * m, sizeof(int));
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
    printf("Enter size of matrix: \n");
    int countOfSize = scanf("%d %d", n, m);
    if (countOfSize == COUNT_OF_SIZE) {
        result = SUCCESS;
        if (*n < 0 || *m < 0) {
            result = ERROR;
        }
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

int findLastMinElem(int **mat, int n, int m) {
    int min;
    if (n > 1) {
        min = **(mat + 1);
    }
    int rowWithMin = NO_STRING_TO_DELETE;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i && j < m; j++) {
            if (*(*(mat + i) + j) <= min) {
                min = *(*(mat + i) + j);
                rowWithMin = i;
            }
        }
    }

    return rowWithMin;
}

void deleteRowWithLastMin(int **mat, int rowWithMin, int* n) {
    if (rowWithMin != NO_STRING_TO_DELETE) {
        for (int i = rowWithMin; i < *n - 1; i++) {
            *(mat + i) = *(mat + i + 1);
        }
        *n -= 1;
    }
}
