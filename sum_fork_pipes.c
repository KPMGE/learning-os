// NOTE: this is a simple program that creates 2 processes to compute the sum of
// the elements of a vector.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

#define CAP 100

int main(int argc, char *argv[]) {
  // alloc array
  int arr[CAP]; 
  srand(time(NULL));

  for (int i = 0; i < CAP; i++) {
    arr[i] = rand() % 10;
  }

  // create a pipe
  int fd[2];
  if (pipe(fd) == -1) {
    perror("error when creating pipe");
    exit(-1);
  }

  // start and end of the vector to be summed up
  int start = 0, end = 0;

  // crate a child process
  pid_t pid = fork();
  if (pid == -1) {
    perror("error when creating fork");
    exit(-1);
  }

  // if we're in the child process, start from 0 and sum up to the middle 
  // otherwise start from the middle and sum up to the end
  if (pid == 0) {
    start = 0;
    end = CAP / 2;
  } else {
    start = CAP / 2;
    end = CAP;
  }

  // compute sum
  int sum = 0;
  for (int i = start; i < end; i++) {
    sum += arr[i];
  }

  printf("partial sum: %d\n", sum);

  // if in the child process, write the sum into the pipe
  if (pid == 0) {
    // close the read end of the pipe as we don't use it here
    close(fd[0]);

    // write sum into the pipe
    if (write(fd[1], &sum, sizeof(sum)) == -1) {
      perror("error when writing partial sum");
      exit(-1);
    }

    // close the write end of the pipe
    close(fd[1]);
  } else {
    // close the write end of the pipe cuz we don't use it here
    close(fd[1]);

    // read sum from child process
    int partial_sum_from_child;
    if (read(fd[0], &partial_sum_from_child, sizeof(int)) == -1) {
      perror("error when reading from the pipe");
      exit(-1);
    }

    // compute total sum
    int total_sum = sum + partial_sum_from_child;
    printf("total sum: %d\n", total_sum);

    // close the read end of the pipe
    close(fd[0]);
    // wait child process to complete its execution 
    wait(NULL);
  }
}
