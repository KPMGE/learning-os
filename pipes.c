#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int fd[2];
  // fd[0] - read end of the pipe
  // fd[1] - write end of the pipe

  if (pipe(fd) == -1)  {
    fprintf(stderr, "failed to create pipe\n");
    exit(-1);
  }
 
  pid_t pid = fork();
  if (pid == -1) {
    fprintf(stderr, "failed to create fork\n");
    exit(-1);
  }

  if (pid == 0) {
    // we close the read end cuz we don't read anything from the pipe
    close(fd[0]);

    int num;
    printf("Enter a number buddy: ");
    scanf("%d", &num);

    // write the numbere read into the write end of the pipe
    if (write(fd[1], &num, sizeof(int)) == -1) {
      fprintf(stderr, "failed to write data into the pipe\n");
      exit(-1);
    }

    // we're done writing to the pipe, so we close it
    close(fd[1]);
  } else {
    wait(NULL);
    // we close the read end of the pipe cuz we don't use it here
    close(fd[1]);

    // read the number from the pipe and store it into the variable
    int num_from_child;
    if (read(fd[0], &num_from_child, sizeof(int)) == -1) {
      fprintf(stderr, "error when reading from the pipe\n");
    }

    printf("Got the number from child process: %d\n", num_from_child);
  }
}
