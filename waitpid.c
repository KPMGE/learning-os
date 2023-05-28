// example of waitpid in action

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
    printf("i'm the child process and i'll exit with status code 10\n");
    sleep(10);
    exit(10);
  } else {
    int code_from_child;
    for (;;) {
      if (!waitpid(pid, &code_from_child, WNOHANG)) {
        printf("child has not been finished yet!\n");
        sleep(1);
      } else {
        printf("my child has been finished with code: %d\n", WEXITSTATUS(code_from_child));
        break;
      }
    }
  }
}
