// example of how to keep an execution order using semaphores in c.

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

sem_t semaphore;

void *routine_1(void *arg) {
  int sleep_time = *(int *)arg;
  printf("hello from routine 1\n");
  sleep(sleep_time);

  sem_post(&semaphore);
  // this print should execute before the one from routine_2
  printf("hey, routine_2, i've executed first lol!\n");
  return NULL;
}

void *routine_2(void *arg) {
  printf("hello from routine 2\n");
  sleep(1);

  sem_wait(&semaphore);
  // this should execute after the one from routine_1
  printf("hey bro, got it, you executed first, don't mess with me ok?\n");

  return NULL;
}

int main(int argc, char **argv) {
  // start semaphore with value 0
  sem_init(&semaphore, 0, 0);

  // threads for the 2 routines
  pthread_t t1, t2;

  // sleep time for each thread
  int sleep_t1 = 2, sleep_t2 = 1;

  if (pthread_create(&t1, NULL, routine_1, &sleep_t1) == -1) {
    perror("error when creating thread: ");
    exit(-1);
  }

  if (pthread_create(&t2, NULL, routine_2, &sleep_t2)) {
    perror("error when creating thread: ");
    exit(-1);
  }

  if (pthread_join(t1, NULL)) {
    perror("error when joining thread: ");
    exit(-1);
  }

  if (pthread_join(t2, NULL)) {
    perror("error when joining thread: ");
    exit(-1);
  }

  sem_destroy(&semaphore);
}
