// sample of how to get the return value of a thread in c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void *roll_dice() {
  int value = (rand() % 6) + 1;
  int *pvalue = malloc(sizeof(int));
  *pvalue = value;
  return pvalue;
}

int main(int argc, char **argv) {
  srand(time(NULL));

  pthread_t t1;

  if (pthread_create(&t1, NULL, roll_dice, NULL) != 0) {
    perror("error when creating thread: ");
    exit(-1);
  }

  int *value_from_thread;
  if (pthread_join(t1, (void **) &value_from_thread) != 0) {
    perror("error when creating thread: ");
    exit(-1);
  }

  printf("generated value: %d", *value_from_thread);

  free(value_from_thread);
}
