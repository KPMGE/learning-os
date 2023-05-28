// siple example of signal usage 

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler();
void apply_handler(int signal, void (*handler)(int));
void reset_handlers(int *signals, int sz);
void sigsuspend_handler();

int main(int argc, char **argv) {
  int blocked_signals[2] = { SIGINT, SIGTSTP };

  printf("dude, i've replaced the SIGINT and SIGTSTP implementations for 1m try using them...\n");

  apply_handler(SIGINT, sigint_handler);
  apply_handler(SIGTSTP, sigsuspend_handler);

  int n = 0;
  printf("if you wanna reset the handlers, enter 1: \n");
  scanf("%d", &n);

  if (n == 0) {
    reset_handlers(blocked_signals, 2);
  }
}

void sigint_handler() {
  printf("dude, you've sent me a SIGINT, wft?\n");
}

void sigsuspend_handler() {
  printf("dude, you've sent me a SIGTSTP, wft?\n");
}

void apply_handler(int signal, void (*handler)(int)) {
  struct sigaction action;

  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  sigaction(signal, &action, NULL);
}

void reset_handlers(int *signals, int sz) {
  struct sigaction action;
  action.sa_handler = SIG_DFL;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  for (int i = 0; i < sz; i++) {
    sigaction(signals[i], &action, NULL);
  }
}
