#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include "entities/student/student.h"
#include "ADTs/list/list.h"

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

    for (int i = 0; i < 2; i++) {
        sleep(rand() % 2 + 3);

        pthread_mutex_lock(&list_mutex);
        int index = get_index(list, student->level);
        to_list(list, student, index);
        printf("\n%s entra na fila - Id = %lu - Fila = %lu",
               student->name,
               student->id,
               list->node->student.id
        );
        fflush(stdout);

        if (list->oven_student != student->id) {
            printf("\n%s esperando por wait", student->name);
            fflush(stdout);
            int rc = pthread_cond_wait(student->condition, &list_mutex);
            assert(rc == 0);
            printf("\n%s foi sinalizado", student->name);
            fflush(stdout);
        }
        pthread_mutex_unlock(&list_mutex);

        pthread_mutex_lock(&oven_mutex);
        printf("\n%s esta usando o forno", student->name);
        fflush(stdout);
        sleep(1);

        pthread_mutex_lock(&list_mutex);
        unlist(list, student->name);
        printf("\n%s libera o forno", student->name);
        fflush(stdout);

        if (!empty(list)) {
            list->oven_student = list->node->student.id;
            int rc = pthread_cond_signal(list->node->student.condition);
            assert(rc == 0);
            printf("\nEmitiu signal para %s", list->node->student.name);
            fflush(stdout);
        } else {
            list->oven_student = -1;
            printf("\nNao tinha ninguem");
            fflush(stdout);
        }
        pthread_mutex_unlock(&list_mutex);
        pthread_mutex_unlock(&oven_mutex);
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
        rc = pthread_create(&(students[i].id), NULL, task, (void *) &(students[i]));
        assert(rc == 0);
    }

    while (student_init < STUDENTS_QUANTITY);
    pthread_cond_broadcast(&initilize);

    for (int i = 0; i < STUDENTS_QUANTITY; ++i) {
        rc = pthread_join(students[i].id, NULL);
        assert(rc == 0);
    }

    return 0;
}
