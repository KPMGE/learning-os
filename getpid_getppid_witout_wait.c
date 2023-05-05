// in this program we create a child process and sleep for 1 second so the
// parent process gets finished. We can see that, once the parent has been
// completed, the child processs gets adopted by another process, usually the
// init process, with id = 1. This behavior occurs cuz we're not waiting the
// child process to complete its execution on the parent process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();

  if (pid == -1) {
    fprintf(stderr, "failed to fork process");
    exit(-1);
  }

  if (pid == 0) {
    sleep(1);
    printf("Child process. pid: %d, parent_id: %d\n", getpid(), getppid());
  } else {
    printf("Parent process. pid: %d, parent_id: %d\n", getpid(), getppid());
  }
}
