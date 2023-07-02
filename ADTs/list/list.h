#ifndef OVEN_SHARE_LIST_H
#define OVEN_SHARE_LIST_H
#define COD_OUT 0
#define COD_IN 1
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../entities/student/student.h"

typedef struct Node {
    Student student;
    struct Node *next;
} Node;

typedef struct List {
    int size;
    Node *node;
    pthread_t oven_student;
} List;

Node *new_node(Student *student);

bool empty(List *list);

bool full(List *list);

List *new_list();

void to_list(List *list, Student *student, int index);

Node *unlist(List *list, char *name);

int get_index(List *list, Level level);

int input(List *list, Student *student);

int output(List *list, Student *student);

void handler(pthread_mutex_t *list_mutex, List *list, Student *student, int (*operation)(List *, Student *));

#endif //OVEN_SHARE_LIST_H
