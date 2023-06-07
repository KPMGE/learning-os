// Really simple example with binary semaphores in C 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>

#define THREAD_CAP 5

sem_t semaphore;

void *routine(void *args) {
  sem_wait(&semaphore);
    // critical region
    sleep(1);
    printf("hello world from thread %d\n", *(int *)args);
  sem_post(&semaphore);

  return NULL;
}

int main(int argc, char **argv) {
  // initialize semaphore with value 1 (binary semaphore)
  sem_init(&semaphore, 0, 1);

  pthread_t threads[THREAD_CAP];

  for (int i = 0; i < THREAD_CAP; i++) {
    // allocate the value to be passed to the thread
    int *arg = malloc(sizeof(int));
    *arg = i + 1;

    if (pthread_create(&threads[i], NULL, routine, arg) == -1) {
      perror("error when creating thread: ");
      exit(-1);
    } 
  }

  for (int i = 0; i < THREAD_CAP; i++) {
    if (pthread_join(threads[i], NULL) == -1) {
      perror("error when joining thread: ");
      exit(-1);
    } 
  }

  sem_destroy(&semaphore);
}
