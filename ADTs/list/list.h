#ifndef OVEN_SHARE_LIST_H
#define OVEN_SHARE_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../entities/student/student.h"

typedef struct Node {
    Student student;
    struct Node *next;
} Node;

typedef struct List {
    Node *node;
    int size;
} List;

Node *new_node(Student *student);

bool empty(List *list);

bool full(List *list);

List *new_list();

void to_list(List *list, Student *student, int index);

Node *unlist(List *list, char *name);

int get_index(List *list, Level level);

void handler(List *list, Student *student, pthread_mutex_t *list_mutex, pthread_mutex_t *oven_mutex);

#endif //OVEN_SHARE_LIST_H
