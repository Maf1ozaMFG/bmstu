#include "mylib.h"

int main() {
    int amount = 0;
    if (inputAmount(&amount)) {
        Student* class = allocMemory(amount);
        if (class != NULL) {
            if (inputStudents(class, amount)) {

                class = deleteStudent(class, &amount);

                findMinMark(class, amount);
                findAvgMark(class, amount);

                sortBySurname(class, amount, compare);
                sortByAverageMark(class, amount);

                outputByMarks(class, amount);
            } else {
                printf("Incorrect input\n");
            }
        } else {
            printf("Incorrect input\n");
        }
        deallocMemory(class);
    } else {
        printf("Incorrect input\n");
    }
}

