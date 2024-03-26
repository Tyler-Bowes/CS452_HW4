#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "deq.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

// static void put(Rep r, End e, Data d) {
// static Data get(Rep r, End e)         { 

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t put;
  pthread_cond_t get;
  int max; // hard coded to 10
  void* r;
} *wrapperRep;

//create function to create
// new put delete and free

wrapperRep wrapper_new(int max) {
  wrapperRep rep = malloc(sizeof(*rep));
  // if (rep == NULL) {
  //   error_sys("malloc error");
  // }
  pthread_mutex_init(&rep->lock, NULL);
  pthread_cond_init(&rep->put, NULL);
  pthread_cond_init(&rep->get, NULL);
  rep->max = max;
  rep->r = deq_new();
  
  return rep;
}

void wrapper_free(wrapperRep rep) {
  pthread_mutex_destroy(&rep->lock);
  pthread_cond_destroy(&rep->put);
  pthread_cond_destroy(&rep->get);
  deq_del(rep->r, 0);
  free(rep);
}


void wrapper_put(wrapperRep rep, Data mole) {
  // put a mole on the lawn if lawn is not full

  pthread_mutex_lock(&rep->lock);
  while (deq_len(rep->r) == rep->max) {
    pthread_cond_wait(&rep->put, &rep->lock);
  }
  deq_tail_put(rep->r, mole);
  pthread_cond_signal(&rep->get); // signal that the lawn is not empty
  pthread_mutex_unlock(&rep->lock);
}

// pthread_cond_init(&decrable,0);

Data wrapper_get(wrapperRep rep) {
  // get a mole from the lawn if lawn is not empty
  
  pthread_mutex_lock(&rep->lock);  
  while (deq_len(rep->r) == 0) {
    pthread_cond_wait(&rep->get, &rep->lock);
  }
  Data mole = deq_head_get(rep->r); // the end can be a random call?
  pthread_cond_signal(&rep->put); // signal that the lawn is not full
  pthread_mutex_unlock(&rep->lock);
  return mole;
}


