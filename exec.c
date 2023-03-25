// NOTE: the exec command is quite useful as it allows us to replace a child process,
// which is an almos identical copy of the parent process with a completely different program.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  int pid = fork();

  if (pid < 0) {
    fprintf(stderr, "error when creating fork\n");
    exit(1);
  }

  if (pid == 0) {
    printf("i'm a child process!\n");
    // replace the child process by the ls command
    printf("replacing child process by ls...\n");
    execvp("ls", NULL);
    fprintf(stderr, "should not be executed\n");
  } else {
    printf("i'm a parent process with pid = %d\n", getpid());
  }
}
