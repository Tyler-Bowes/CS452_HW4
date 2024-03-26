#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

// Function declarations
pthread_t * create_thread(void* (*start_routine)(void*), void* arg, int Num);
void consume_thread(pthread_t *tids, int Num);

#endif

