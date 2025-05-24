#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "mylib.h"

void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

Student* allocMemory(int amount) {
    return (Student*)calloc(amount, sizeof(Student));
}

int inputAmount(int* amount) {
    int checkAmount = scanf("%d", amount);
    return checkAmount && *amount > 0 ? SUCCESS : ERROR;
}

int inputStudents(Student* class, int amount) {
    int result = SUCCESS;
    for (int i = 0; i < amount; i++) {
        int flagSurname = scanf("%50s", class[i].surname);
        if (!flagSurname) {
            result = ERROR;
        }
        for (int j = 0; j < AMOUNT_OF_MARKS; j++) {
            int flagMarks = scanf("%d", class[i].marks + j);
            if (!flagMarks || class[i].marks[j] < MIN_MARK || class[i].marks[j] > MAX_MARK) {
                result = ERROR;
            }
        }
    }
    return result;
}

void findMinMark(Student* class, int amount) {
    for (int i = 0; i < amount; i++) {
        int minMark = class[i].marks[0];
        for (int j = 0; j < AMOUNT_OF_MARKS; j++) {
            if (class[i].marks[j] < minMark) {
                minMark = class[i].marks[j];
            }
        }
        class[i].groupOfStudent = minMark;
    }
}

void sortBySurname(Student* class, int amount, int(*cmp)(Student*, Student*)) {
    for (int i = 0; i < amount - 1; i++) {
        for (int j = i + 1; j < amount; j++) {
            if (cmp(class + i, class + j) > 0) {
                swap(class + i, class + j);
            }
        }
    }
}

void outputStudent(Student* class) {
    printf("%s\n", class->surname);
    for (int i = 0; i < AMOUNT_OF_MARKS; i++) {
        printf("%d ", class->marks[i]);
    }
    printf("\n");
}

int checkMarks(Student* class, int amount, int mark) {
    int result = ERROR;
    for (int i = 0; i < amount; i++) {
        if (class[i].groupOfStudent == mark) {
            result = SUCCESS;
            break;
        }
    }
    return result;
}

void outputWithMarks(Student* class, const int amount, const int mark) {
    for (int i = 0; i < amount; i++) {
        if (class[i].groupOfStudent == mark) {
            outputStudent(class + i);
        }
    }
    printf("\n");
}

void outputByMarks(Student* class, const int amount) {
    if (checkMarks(class, amount, A)) {
        printf("A-students:\n");
        outputWithMarks(class, amount, A);
    }
    if (checkMarks(class, amount, B)) {
        printf("B-students:\n");
        outputWithMarks(class, amount, B);
    }
    if (checkMarks(class, amount, C)) {
        printf("C-students:\n");
        outputWithMarks(class, amount, C);
    }
    if (checkMarks(class, amount, D)) {
        printf("D-students:\n");
        outputWithMarks(class, amount, D);
    }
}

void deallocMemory(Student* arr) {
    free(arr);
}

int compare(Student* a, Student* b) {
    return myStrcmp(a->surname, b->surname);
}