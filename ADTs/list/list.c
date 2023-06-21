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
    new_list->node = NULL;
    new_list->size = 0;
    return new_list;
}

void to_list(List *list, Student *student, int index) {
    if (full(list)) return;
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
    while(current != NULL && strcmp(current->student.name, name) != 0) {
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
    while (aux != NULL && level >= aux->student.level) {
        aux = aux->next;
        i++;
    }
    return i;
}

void handler(List *list, Student *student, pthread_mutex_t *mutex) {
    if (empty(list)) student->turn = true;
    int index = get_index(list, student->level);
    to_list(list, student, index);
    printf("\n%s entra na fila - Id = %lu - Fila = %lu", student->name, student->id, list->node->student.id);
    fflush(stdout);
    while(!student->turn) {
        printf("\nEsperando o signal %lu", student->id);
        pthread_cond_wait(&student->condition, mutex);
        printf("\nCapturei o signal %lu", student->id);
    }
    printf("\nProssegui");
}