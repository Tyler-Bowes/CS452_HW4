#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "deq.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

// static void put(Rep r, End e, Data d) {
// static Data get(Rep r, End e)         { 

typedef enum {Head,Tail,Ends} End;

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t put;
  pthread_cond_t get;
  int max; // hard coded to 10
  void* r;
} *wrapperRep;

//create function to create
// new put delete and free

static wrapperRep wrapper_new(int max) {
  wrapperRep rep = malloc(sizeof(*rep));
  // if (rep == NULL) {
  //   error_sys("malloc error");
  // }
  
  if (pthread_mutex_init(&rep->lock, NULL) != 0) {
    error_sys("mutex init error");
  }
  
  if (pthread_cond_init(&rep->put, NULL) != 0) {
    error_sys("condition variable init error");
  }
  
  if (pthread_cond_init(&rep->get, NULL) != 0) {
    error_sys("condition variable init error");
  }
  
  rep->max = max;
  rep->r = deq_new();
  
  return rep;
}

wrapper_free(wrapperRep rep) {
  pthread_mutex_destroy(&rep->lock);
  pthread_cond_destroy(&rep->put);
  pthread_cond_destroy(&rep->get);
  deq_free(rep->r);
  free(rep);
}


static void wrapper_put(wrapperRep rep, Data mole, End end) {
  // put a mole on the lawn if lawn is not full

  pthread_mutex_lock(&rep->lock);
  while (deq_len(rep->r) == 10) {
    pthread_cond_wait(&rep->put, &rep->lock);
  }
  deq_put(rep->r, end, mole);
  pthread_cond_signal(&rep->get); // signal that the lawn is not empty
  pthread_mutex_unlock(&rep->lock);
}

// pthread_cond_init(&decrable,0);

static Data wrapper_get(wrapperRep rep, End end) {
  // get a mole from the lawn if lawn is not empty
  
  pthread_mutex_lock(&rep->lock);  
  while (deq_len(rep->r) == 0) {
    pthread_cond_wait(&rep->get, &rep->lock);
  }
  Data mole = deq_get(rep->r, end); // the end can be a random call?
  pthread_cond_signal(&rep->put); // signal that the lawn is not full
  pthread_mutex_unlock(&rep->lock);
  return mole;
}


