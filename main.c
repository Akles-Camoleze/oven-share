#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include "entities/student/student.h"
#include "ADTs/list/list.h"

/*
 * Trancar a mutex do forno
 * Verificar se a fila esta vazia, caso, sim, entrar na fila, usar, sair da fila e emitir signal para o proximo
 * Caso nao estiver vazia, verificar se é o primeiro, se for, usar, sair da fila e emitir o signal para o proximo
 * Caso nao seja o primeiro dar um wait
 */

int student_init;
List *list;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oven_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t initilize = PTHREAD_COND_INITIALIZER;

void *task(void *argument) {
    Student *student = (Student *) argument;

    //broadcast
    pthread_mutex_lock(&mutex);
    student_init++;
    pthread_cond_wait(&initilize, &mutex);
    pthread_mutex_unlock(&mutex);
/*
 * Trancar a mutex do forno
 * Verificar se a fila esta vazia, caso, sim, entrar na fila, usar, sair da fila e emitir signal para o proximo
 * Caso nao estiver vazia, verificar se é o primeiro, se for, usar, sair da fila e emitir o signal para o proximo
 * Caso nao seja o primeiro dar um wait
 */
    for (int i = 0; i < 1; i++) {
        sleep(rand() % 2 + 3);

        pthread_mutex_lock(&list_mutex);
        printf("\n%s travou a lista", student->name);
        int index = get_index(list, student->level);
        to_list(list, student, index);
        printf("\n%s entra na fila - Id = %lu - Fila = %lu",
               student->name,
               (unsigned long) student->id,
               (unsigned long) list->node->student.id
        );

        while (list->oven_student != student->id) {
            printf("\n%s esperando por wait", student->name);
            pthread_cond_wait(&student->condition, &list_mutex);
            printf("\n%s foi sinalizado", student->name); // linha A
        }
        pthread_mutex_lock(&oven_mutex);

        pthread_mutex_unlock(&list_mutex);
        printf("\n%s destravou a lista", student->name);

        printf("\n%s esta usando o forno", student->name);
        sleep(1);

        pthread_mutex_lock(&list_mutex);
        unlist(list, student->name);
        printf("\n%s libera o forno", student->name);
        printf("\n------------------------");
        Node *aux = list->node;
        while (aux != NULL) {
            printf("\n%s", aux->student.name);
            aux = aux->next;
        }
        printf("\n------------------------");
        if (!empty(list)) {
            list->oven_student = list->node->student.id;
            pthread_cond_signal(&list->node->student.condition);
            printf("\nEmitiu signal para %s", list->node->student.name);
        } else {
            list->oven_student = NULL;
            printf("\nNao tinha ninguem");
        }
        pthread_mutex_unlock(&list_mutex);
        printf("\n%s destravou a lista", student->name);
        pthread_mutex_unlock(&oven_mutex);
        printf("\n%s destravou o forno", student->name);

    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    int rc;
    list = new_list();
    student_init = 0;
    Student students[STUDENTS_QUANTITY];
    create_students(students);
    srand(time(NULL));

    for (int i = 0; i < STUDENTS_QUANTITY; ++i) {
        rc = pthread_create(&students[i].id, NULL, task, (void *) &students[i]);
        assert(rc == 0);
    }

    while (student_init < STUDENTS_QUANTITY);
    pthread_cond_broadcast(&initilize);

    for (int i = 0; i < STUDENTS_QUANTITY; ++i) {
        rc = pthread_join(students[i].id, NULL);
        assert(rc == 0);
    }

//    int index = get_index(list, students[2].level);
//    to_list(list, &students[2], index);
//    printf("\n%d", index);
//
//    index = get_index(list, students[4].level);
//    to_list(list, &students[4], index);
//    printf("\n%d", index);
//    unlist(list, students[2].name);
//
//    index = get_index(list, students[0].level);
//    to_list(list, &students[0], index);
//    printf("\n%d", index);
//
//    index = get_index(list, students[5].level);
//    to_list(list, &students[5], index);
//    printf("\n%d", index);
//
//    index = get_index(list, students[3].level);
//    to_list(list, &students[3], index);
//    printf("\n%d", index);
//
//    index = get_index(list, students[1].level);
//    to_list(list, &students[1], index);
//    printf("\n%d", index);

//    unlist(list, students[0].name);
//    unlist(list, students[1].name);
//    unlist(list, students[2].name);
//    unlist(list, students[3].name);
//    unlist(list, students[4].name);
//    unlist(list, students[5].name);
//

    Node *aux = list->node;
    while (aux != NULL) {
        printf("\n%s", aux->student.name);
        aux = aux->next;
    }

    return 0;
}
