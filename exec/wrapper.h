#ifndef WRAPPER_H
#define WRAPPER_H

#include "deq.h"

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t put;
    pthread_cond_t get;
    int max;
    void* r;
} *wrapperRep;
typedef void* Data;

// Function declarations
extern wrapperRep wrapper_new(int max);
extern void wrapper_free(wrapperRep rep);
extern void wrapper_put(wrapperRep rep, Data mole);
extern Data wrapper_get(wrapperRep rep);

#endif