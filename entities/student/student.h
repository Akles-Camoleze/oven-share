#ifndef OVEN_SHARE_STUDENT_H
#define OVEN_SHARE_STUDENT_H
#define STUDENTS_QUANTITY 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "names.h"
#include "../../enums/level/level.enum.h"

typedef struct Student {
    int id;
    int waiting;
    char *name;
    Level level;
} Student;

Student *new_student(char* name, Level level);

void create_students();

#endif //OVEN_SHARE_STUDENT_H