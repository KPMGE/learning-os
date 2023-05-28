// example of how to block signals in c using sigprocmask

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void block_signals(int *signals, int n);
void unblock_signals(int *signals, int n);

int main(int argc, char **argv) {
  int seconds = 10;
  int signals_to_blck[2] = { SIGINT, SIGTSTP };

  printf("hahaha SIGINT and SIGTSTP have been blocked for %d seconds dude, try using them..\n", seconds);

  block_signals(signals_to_blck, 2);
  sleep(seconds);

  printf("Ok bro, got it know..\n");
  unblock_signals(signals_to_blck, 2);
}

void block_signals(int *signals, int n) {
  // define mask
  sigset_t mask;
  sigemptyset(&mask);

  // add blocked signals to the mask
  for (int i = 0; i < n; i++) {
    sigaddset(&mask, signals[i]);
  }

  // block signals
  sigprocmask(SIG_BLOCK, &mask, NULL);
}

void unblock_signals(int *signals, int n) {
  // define mask
  sigset_t mask;
  sigemptyset(&mask);

  // add blocked signals to the mask
  for (int i = 0; i < n; i++) {
    sigaddset(&mask, signals[i]);
  }

  // block signals
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
}
