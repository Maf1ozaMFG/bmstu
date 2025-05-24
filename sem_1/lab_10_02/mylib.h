#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mystring.h"

#define SUCCESS 1
#define ERROR 0

#define AMOUNT_OF_MARKS 4

#define MIN_MARK 2
#define MAX_MARK 5

#define MAX_LEN 50

enum MARK {
    D = 2,
    C,
    B,
    A
};

typedef struct {
    char surname[MAX_LEN];
    int marks[AMOUNT_OF_MARKS];
    int groupOfStudent;
    float averageMark;
} Student;

void swap(Student* a, Student* b);

int inputAmount(int* amount);
int inputStudents(Student* class, int amount);

void outputStudent(Student* class);
void outputWithMarks(Student* class, const int amount, const int mark);
void outputByMarks(Student* class, const int amount);

void findMinMark(Student* class, int amount);
void findAvgMark(Student* class, const int amount);

int checkMarks(Student* class, int amount, int mark);
Student* deleteStudent(Student* class, int* amount);

void sortByAverageMark(Student* class, int amount);
void sortBySurname(Student* class, int amount, int(*cmp)(Student*, Student*));

Student* allocMemory(int amount);
void deallocMemory(Student* arr);

int compare(Student* a, Student* b);

#endif // MYLIB_H
