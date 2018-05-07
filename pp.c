#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

void
die(char *msg, ...)
{
  va_list ap;

  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  exit(1);
}

void
sigint(const int signo)
{
  printf("Why you interrupted me?\n");
  printf("  Why don't you respect my concentration\n");
  exit(0);
}

int
main(int argc, char *argv[])
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sigint;
  if(sigaction(SIGINT, &sa, NULL))
    die("Could not setup sigterm handler\n");

  for(;;)
  {
  }
 
  return EXIT_SUCCESS;
}
