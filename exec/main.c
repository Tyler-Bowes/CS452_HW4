#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include <pthread.h>
#include "wrapper.h"
#include "threads.h"
 
static void *produce(void *a) { 
  void **arg=a;
  wrapperRep q=(wrapperRep)arg[0];
  Lawn l=(Lawn)arg[1];
  wrapper_put(q,mole_new(l,0,0));
  return 0;
}
static void *consume(void *a) { 
  void **arg=a;
  wrapperRep q=(wrapperRep)arg[0];
  Mole m=wrapper_get(q);
  mole_whack(m);
  return 0;
}

int main() {
  srandom(time(0));
  const int n=10;
  Lawn lawn=lawn_new(0,0);

  wrapperRep mtq = wrapper_new(10);

  void *arg[2]={mtq,lawn};

  // need to create produce_thr and consume_thr variables to hold the threads
  pthread_t *produce_thr = create_thread(produce, arg, n);
  pthread_t *consume_thr = create_thread(consume, arg, n);

  // call produce and consume functions while consume_thread
  consume_thread(produce_thr, n);
  consume_thread(consume_thr, n);
  
  wrapper_free(mtq);
  lawn_free(lawn);

  // for (int i=1; i<=n; i++)
  //   consume(produce(lawn));
  // lawn_free(lawn);
}
