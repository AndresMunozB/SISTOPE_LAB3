#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_COUNT 4
#define BARRIER_COUNT 6

pthread_barrier_t barriers[BARRIER_COUNT];
pthread_barrier_t barriers2[BARRIER_COUNT];

void* threadFn(void *id_ptr) {
  int thread_id = *(int*)id_ptr;
  

  int i;
  for (i=0;i<BARRIER_COUNT;i++){
    int wait_sec = 1 + rand() % 5;
    printf("thread %d: Wait for %d seconds.\n", thread_id, wait_sec);
    sleep(wait_sec);
    printf("thread %d: I'm ready...\n", thread_id);
    pthread_barrier_wait(&barriers[i]);
    printf("thread %d: going! step:%d\n", thread_id,i);
  }

  
  return NULL;
}


int main() {
  int i;
  pthread_t ids[THREAD_COUNT];
  int short_ids[THREAD_COUNT];

  srand(time(NULL));


  for (i=0;i<BARRIER_COUNT;i++){
      pthread_barrier_init(&barriers[i], NULL, THREAD_COUNT );

  }

  for (i=0; i < THREAD_COUNT; i++) {
    short_ids[i] = i;
    pthread_create(&ids[i], NULL, threadFn, &short_ids[i]);
  }


  for (i=0; i < THREAD_COUNT; i++) {
    pthread_join(ids[i], NULL);
  }

  for (i=0;i<BARRIER_COUNT;i++){
    pthread_barrier_destroy(&barriers[i]);

  }

  return 0;
}