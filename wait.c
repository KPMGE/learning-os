// the main program prints numbers from 6 to 10 and the child one prints numbers
// from 0 to 5. And we want them to be printed in the ascending order

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();

  if (pid == -1) {
    fprintf(stderr, "error when forking process");
    exit(-1);
  }

  if (pid == 0) {
    for (int i = 0; i <= 5; i++) {
      printf("%d ", i);
    }
  } else {
    wait(NULL);
    for (int i = 6; i <= 10; i++) {
      printf("%d ", i);
    }
  }
}
