#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include "entities/student/student.h"
#include "ADTs/list/list.h"
#include "services/services.h"

int loops;
List *list;
int student_count;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oven_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t initilize = PTHREAD_COND_INITIALIZER;

void *task(void *argument) {
    Student *student = (Student *) argument;

    await_broadcast(&mutex, &initilize, &student_count);

    for (int i = 0; i < loops; i++) {
        sleep(rand() % 2 + 3);

        handler(&list_mutex, list, student, input);

        pthread_mutex_lock(&oven_mutex);
        printf("\n%s esta usando o forno", student->name);
        fflush(stdout);
        sleep(1);

        handler(&list_mutex, list, student, output);

        pthread_mutex_unlock(&oven_mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }
    loops = (int) strtol(argv[1], NULL, 10);
    int rc;
    list = new_list();
    student_count = 0;
    Student students[STUDENTS_QUANTITY];
    create_students(students);
    srand(time(NULL));

    for (int i = 0; i < STUDENTS_QUANTITY; ++i) {
        rc = pthread_create(&(students[i].id), NULL, task, (void *) &(students[i]));
        assert(rc == 0);
    }

    while (student_count < STUDENTS_QUANTITY);
    pthread_cond_broadcast(&initilize);

    for (int i = 0; i < STUDENTS_QUANTITY; ++i) {
        rc = pthread_join(students[i].id, NULL);
        assert(rc == 0);
    }

    return 0;
}
