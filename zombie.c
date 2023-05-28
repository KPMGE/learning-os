// sample of zombie processes.
// NOTE: you can use 'ps au' to see all processes running for your user, 
// after 10s you should see that the child process has become a zombie process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t pid = fork();

  if (pid < 0) {
    perror("Fork error: ");
    exit(-1);
  }

  if (pid == 0) {
    printf("i'm the child process, i'll sleep for 1s and exit.");
    sleep(10);
    // loop, so as the parent won't execute the wait function, this process will
    // the child executes exit, but the parent process is gonna be on a for
    // become a zombie one.
    exit(1);
  } else {
    for (;;);
  }
}
