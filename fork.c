#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  // creates a fork of the current program
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    printf("hi, i'm a child process!\n");
    printf("child process doing stuff...\n");
    sleep(5);
  } else {
    printf("hi, i'm the father process!\n");
    // wait for child process to complete, returning the child pid
    int child_pid = wait(NULL);

    if (child_pid == -1) {
      fprintf(stderr, "error when waiting child process to complete!\n");
      exit(1);
    }

    printf("i got a pid = %d and my child process, with pid = %d is done!\n", child_pid, getpid());
  }
}
