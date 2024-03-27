#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// create threads that refernce a function to run
pthread_t * create_thread(void* (*start_routine)(void*), void* arg, int Num) {
    
    pthread_t *tids =  (pthread_t * ) malloc(sizeof(pthread_t) * Num);
    for (int i=0; i<Num; i++){
        pthread_create(&tids[i],0,start_routine,arg);
    }

    return tids;
}

// join threads together
void consume_thread(pthread_t *tids, int Num) {
    for (int i=0; i<Num; i++){
        pthread_join(tids[i],0);
    }

    free(tids);
}



