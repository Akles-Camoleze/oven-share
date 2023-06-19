#ifndef OVEN_SHARE_STUDENT_H
#define OVEN_SHARE_STUDENT_H
#define STUDENTS_QUANTITY 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "names.h"
#include "../../enums/level/level.enum.h"

typedef struct Student {
    int waiting;
    char *name;
    pthread_t id;
    Level level;
    Level level_backup;
    pthread_cond_t condition;
} Student;

Student *new_student(char* name, Level level);

void create_students(Student *students);

#endif //OVEN_SHARE_STUDENT_H