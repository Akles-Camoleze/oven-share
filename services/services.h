#ifndef OVEN_SHARE_SERVICES_H
#define OVEN_SHARE_SERVICES_H
#include <pthread.h>
void await_broadcast(pthread_mutex_t *mutex, pthread_cond_t *initilize, int *student_count);
#endif //OVEN_SHARE_SERVICES_H
