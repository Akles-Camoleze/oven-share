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
    new_list->oven_student = NULL;
    return new_list;
}

void to_list(List *list, Student *student, int index) {
    if (full(list)) return;
    if (list->oven_student == NULL) list->oven_student = student->id;
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

void handler(List *list, Student *student, pthread_mutex_t *list_mutex, pthread_mutex_t *oven_mutex) {
    pthread_mutex_lock(list_mutex);
    if (empty(list));
    int index = get_index(list, student->level);
    to_list(list, student, index);
    printf("\n%s entra na fila - Id = %lu - Fila = %lu", student->name, student->id, list->node->student.id);
    fflush(stdout);
    pthread_mutex_unlock(list_mutex);

    pthread_mutex_lock(oven_mutex);
//    if(!student->turn) {
//        printf("\nEsperando o signal %lu", student->id);
//        pthread_cond_wait(&student->condition, oven_mutex);
//        printf("\nCapturei o signal %lu", student->id);
//    }
    printf("\nProssegui");
}