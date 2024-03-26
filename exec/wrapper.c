#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "deq.h"
#include <stdlib.h>
#include <string.h>

int max = 10;
current = 0;

// static void put(Rep r, End e, Data d) {
// static Data get(Rep r, End e)         { 

typedef enum {Head,Tail,Ends} End;

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t put;
  pthread_cond_t get;
  int max;
  void* r;
} *wrapperRep;

//create function to create

static void wrapper_put(wrapperRep rep, Data mole, End end) {
  pthread_mutex_lock(&rep->lock); // lock the mutex
  while (current == max) { // # of moles is at the max for the deq
      pthread_cond_wait(&rep->put, &rep->lock); 
  }
  // put the mole in the lawn
  Deq q = (Deq)rep->r;
  put(q, mole, end); // put the mole in the lawn
  current++; 
  
  pthread_cond_signal(&rep->get); 
  pthread_mutex_unlock(&rep->lock); 
}

// pthread_cond_init(&decrable,0);

static Data wrapper_get(wrapperRep rep, End end) {
  pthread_mutex_lock(&rep->lock); 
  while (current <= 0) { // # of moles is at 0 so cannot take out a mole
      pthread_cond_wait(&rep->get, &rep->lock); 
  }
  // get the mole from the lawn
  Deq q = (Deq)rep->r;
  Data mole = get(q, end); 
  current--;
  pthread_cond_signal(&rep->put); // signal the condition
  pthread_mutex_unlock(&rep->lock); // unlock the mutex
}


