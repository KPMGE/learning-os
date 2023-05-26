// example of how to create multiple threads using for loops in c.
// NOTE: when we create threads using arrays, we need to use 2 for loops, one
// for creating the threads and the other for joining them. Otherwise we're not
// really doing thins concurrently, cuz we will end up creating a thread and
// right after that waiting it finish its execution before creating another one,
// so we'll end up in a sequential execution.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *handler() { return NULL; }

int main(int argc, char **argv) {
  pthread_t threads[8];

  // create threads
  for (int i = 0; i < 8; i++) {
    if (pthread_create(&threads[i], NULL, handler, NULL) != 0) {
      perror("error when creating thread: ");
      exit(-1);
    }
  }

  // join threads
  for (int i = 0; i < 8; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("error when joining thread: ");
      exit(-1);
    }
  }
}
