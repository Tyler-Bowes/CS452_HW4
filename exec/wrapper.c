#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "deq.h"
#include <stdlib.h>
#include <string.h>

int min = 0;
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

static void put(wrapperRep rep, Data mole, End end) {

}

pthread_cond_init(&decrable,0);


if (current == min) {
    pthread_mutex_lock(&lock);

    pthread_mutex_unlock(&lock);
} else if (current == max) {
    pthread_mutex_lock(&lock);

    pthread_mutex_unlock(&lock);
}
