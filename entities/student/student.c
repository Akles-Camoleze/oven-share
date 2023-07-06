#include "student.h"

Student *new_student(char *name, Level level) {
    Student *student = (Student *) malloc(sizeof(Student));
    student->condition = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    int rc = pthread_cond_init(student->condition, NULL);
    assert(rc == 0);
    student->waiting = 0;
    student->name = strdup(name);
    student->level = level;
    student->level_backup = level;

    return student;
}

void create_students(Student *students) {
    Level current_level = SENIOR;
    char names[STUDENTS_QUANTITY][MAX_NAME_SIZE] = ALL_NAMES;
    for (int i = 0; i < STUDENTS_QUANTITY / 2; ++i) {
        students[i * 2] = *new_student(names[i * 2], current_level);
        students[i * 2 + 1] = *new_student(names[i * 2 + 1], current_level);
        current_level++;
    }
}

void reset_attr(Student *student) {
    student->waiting = 0;
    student->level = student->level_backup;
}
