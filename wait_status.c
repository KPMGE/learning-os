// example of wait and waitpid in action
// NOTE: wait is a blocking function by default and it waits for any of the
// children processes to finish.
// NOTE: waitpid allow us specify the pid fo the process to wait for. Moreover,
// we can pass in some options to it, one that's quite useful is WNOHANG, with
// this one, we can test if the child process is done without waiting, so our
// parent process can continue doing some useful work meanwhile.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv) {
  pid_t pid = fork();

  if (pid < 0) {
    perror("fork error: ");
    exit(-1);
  }

  if (pid == 0) {
    printf("hey, i'm the child and i'll terminate with the code 10!\n");
    sleep(1);
    exit(10);
  } else {
    int code_from_child;
    printf("hey i'm the parent process and i'll wait for my child to finish\n");
    wait(&code_from_child);
    int status_from_child = WEXITSTATUS(code_from_child);
    printf("my child has finished and returned the code: %d\n", status_from_child);
  }
}
