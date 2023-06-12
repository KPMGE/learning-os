// simple program to demonstrate how to work with the return value from a child
// process in c.

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <errno.h>

int main() {
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork error: ");
    exit(-1);
  }

  if (pid == 0) {
    const int secs = 10;
    const int status_code = 50;

    printf("[CHILD]: I'm gonna sleep for %d seconds...\n", secs);
    sleep(secs);
    printf("[CHILD]: i'm done and will return the status code %d\n", status_code);
    return status_code;
  } else {
    printf("[PARENT]: child pid: %d\n", pid);

    int child_return_status;
    if (wait(&child_return_status) == -1) {
      perror("wait error: ");
      exit(-1);
    }

    // if child process has been stopped by a signal
    if (WIFSIGNALED(child_return_status)) {
      const int sig_number = WTERMSIG(child_return_status);
      printf("[PARENT]: the child has been stopped by the signal: %d\n", sig_number);
    }

    // if child has exited normally
    if (WIFEXITED(child_return_status)) {
      const int status = WEXITSTATUS(child_return_status);
      printf("[PARENT]: child process finished with status code: %d\n", status);
    }
  }
}
