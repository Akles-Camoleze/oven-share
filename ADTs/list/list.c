#include "list.h"

bool empty(List *list) {
    return list->node == NULL;
}

bool full(List *list) {
    return list->size == STUDENTS_QUANTITY;
}

Node *new_node(Student *student) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->student = *student;
    return node;
}

List *new_list() {
    List *new_list = (List *) malloc(sizeof(List));
    new_list->size = 0;
    new_list->node = NULL;
    new_list->oven_student = -1;
    return new_list;
}

void to_list(List *list, Student *student, int index) {
    if (full(list)) return;
    if (list->oven_student == -1) list->oven_student = student->id;
    Node *current = list->node, *prev = list->node;
    Node *node = new_node(student);
    for (int i = 0; i < index && current != NULL; i++) {
        prev = current;
        current = current->next;
    }
    node->next = current;
    index != 0 ? (prev->next = node) : (list->node = node);
    list->size++;
}

Node *unlist(List *list, char *name) {
    if (empty(list)) return NULL;
    Node *current = list->node, *prev = list->node;
    while (current != NULL && strcmp(current->student.name, name) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return NULL;
    if (prev == current) {
        list->node = list->node->next;
    }
    prev->next = current->next;
    list->size--;
    return current;
}

int get_index(List *list, Level level) {
    int i = 0;
    Node *aux = list->node;
    while (aux != NULL && (level >= aux->student.level || list->oven_student == aux->student.id)) {
        aux = aux->next;
        i++;
    }
    return i;
}
