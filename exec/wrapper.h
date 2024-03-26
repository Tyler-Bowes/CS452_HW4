#ifndef WRAPPER_H
#define WRAPPER_H

#include "deq.h"

typedef enum {Head,Tail,Ends} End;
typedef struct {/*...*/} *wrapperRep;
typedef void* Data;

// Function declarations
wrapperRep wrapper_new(int max);
void wrapper_free(wrapperRep rep);
void wrapper_put(wrapperRep rep, Data mole, End end);
Data wrapper_get(wrapperRep rep, End end);

#endif