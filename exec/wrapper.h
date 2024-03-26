#ifndef WRAPPER_H
#define WRAPPER_H

#include "deq.h"

typedef struct {} *wrapperRep;
typedef void* Data;

// Function declarations
extern wrapperRep wrapper_new(int max);
extern void wrapper_free(wrapperRep rep);
extern void wrapper_put(wrapperRep rep, Data mole);
extern Data wrapper_get(wrapperRep rep);

#endif