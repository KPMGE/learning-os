// here, we have a simple program that creates a fork and then sleeps for 1s on
// the child process, if we're in the parent process, we wait for the child
// process to complete its execution and print out some information.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();

  if (pid == -1) {
    fprintf(stderr, "failed to fork process\n");
    exit(-1);
  }

  if (pid == 0) {
    sleep(1);
    printf("Child process. pid: %d, parent_id: %d\n", getpid(), getppid());
  } else {
    pid_t child_pid = wait(NULL);

    printf("Parent process. pid: %d, parent_id: %d\n", getpid(), getppid());

    if (child_pid == -1) {
      printf("No children to wait for\n");
    } else {
      printf("Process with pid = %d finished execution\n", child_pid);
    }
  }
}
