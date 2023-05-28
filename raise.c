// simple example of raise function in c
// NOTE: the raise function allows us to send a signal to ourselves, this can be
// nice when we want a custom handler but still wanna execute the action
// defined in the default one.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler();
void apply_handler(int signal, void (*handler)(int));
void reset_handler(int signal);

int main(int argc, char **argv) {
  printf("try using CTRL + C\n");

  apply_handler(SIGINT, sigint_handler);

  for(;;);
}

void apply_handler(int signal, void (*handler)(int)) {
  struct sigaction action;

  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  sigaction(signal, &action, NULL);
}

void reset_handler(int signal) {
  struct sigaction act;
  act.sa_handler = SIG_DFL;
  sigaction(signal, &act, NULL);
}

void sigint_handler() {
  printf("hey, i know you've sent a SIGINT to me, but i'll do some stuff and execute the default SIGINT handler, ok?\n");
  // we set back the default handler
  reset_handler(SIGINT);
  // send the same signal to ourselves
  raise(SIGINT);
}
