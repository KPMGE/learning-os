// on unix we have the idea of a groud-id, which enbraces one or more process. 
// All processes with the same group-id are threated as the same entity

// NOTE: the leader of a process group is a process in which the process id and
// the process group are the same

// NOTE: the child processes inherit the group-id from their parent

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  pid_t pid = fork();

  if (pid == -1) {
    perror("Error when forking: ");
    exit(-1);
  }

  if (pid == 0) {
    printf("Child: pid: %d, gpid: %d, ppid: %d\n", getpid(), getpgrp(), getppid());
  } else {
    printf("Parent: pid: %d, gpid: %d\n", getpid(), getpgrp());
    wait(NULL);
  }
}
