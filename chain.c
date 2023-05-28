// simple process chan in c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char **argv) {
  assert(argc == 2);

  pid_t pid;
  for (int i = 0; i < atoi(argv[1]); i++) {
    printf("new process!\n");
    if ((pid = fork())) {
      break;
    }
  }
}
