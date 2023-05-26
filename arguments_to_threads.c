// simple example of how to pass in arguments to threads

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = { 2, 3, 5, 7, 11, 17, 19, 23, 27, 29 };

void *display_prime(void *arg) {
  int *idx = arg;
  printf("%d\n", primes[*idx]);
  free(arg);
  return NULL;
}

int main(int argc, char **argv) {
  pthread_t threads[10];

  for (int i = 0; i < 10; i++) {
    // this approach is problematic, because in the meantime between the
    // execution of the for loop and the creation of the thread, the value of i
    // could change, resulting in the wrong behavior.
    // if (pthread_create(threads + i, NULL, display_prime, &i) != 0) {
    //   perror("error when creating thread: ");
    //   exit(-1);
    // }
    
    // the best approach in here is, for each thread allocate a separate
    // variable on the heap, so it no longer could've been changed when the
    // thread finally gets created. 
    int *allocated_i = malloc(sizeof(int));
    *allocated_i = i;
    if (pthread_create(&threads[i], NULL, display_prime, allocated_i) != 0) {
      perror("error when creating thread: ");
      exit(-1);
    }
  }

  for (int i = 0; i < 10; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("error when creating thread: ");
      exit(-1);
    }
  }
}
