#include "services.h"

void await_broadcast(pthread_mutex_t *mutex, pthread_cond_t *initilize, int *student_count) {
    pthread_mutex_lock(mutex);
    (*student_count)++;
    pthread_cond_wait(initilize, mutex);
    pthread_mutex_unlock(mutex);
}