// mutexes are a good way to protect certain variables to be modified by other
// threads while the current thread runs, which could let to wrong results.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int amount = 0, amount_mutex = 0;

void *increment_amount_no_mutex();
void *increment_amount_mutex();
void spawn_2_threads(void * (*handler)());

int main(int argc, char **argv) {
  pthread_mutex_init(&mutex, NULL);
  // spawn 2 threads that increment the value using mutex
  spawn_2_threads(increment_amount_no_mutex);
  // spawn 2 threads that increment the value without using mutex
  spawn_2_threads(increment_amount_mutex);

  printf("amount without mutex: %d\n", amount);
  printf("amount with mutex: %d\n", amount_mutex);

  pthread_mutex_destroy(&mutex);
}

void *increment_amount_no_mutex() {
  for (int i = 0; i < 1000000; i++) {
    amount++;
  }

  return NULL;
}

void *increment_amount_mutex() {
  for (int i = 0; i < 1000000; i++) {
    // lock mutex, so variables are no longer modifiable
    pthread_mutex_lock(&mutex);
    amount_mutex++;
    // unlock mutex, so now we can mutate then again
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

void spawn_2_threads(void * (*handler)()) {
  pthread_t t1, t2; 

  if (pthread_create(&t1, NULL, handler, NULL) != 0 ) {
    perror("error when creating thread: ");
    exit(-1);
  }

  if (pthread_create(&t2, NULL, handler, NULL) != 0 ) {
    perror("error when creating thread: ");
    exit(-1);
  }


  if (pthread_join(t1, NULL) != 0 ) {
    perror("error when joining thread: ");
    exit(-1);
  }

  if (pthread_join(t2, NULL) != 0 ) {
    perror("error when joining thread: ");
    exit(-1);
  }
}
