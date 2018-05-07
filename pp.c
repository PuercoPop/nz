#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>

void
die(char *msg, ...)
{
  va_list ap;

  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  exit(1);
}

static struct termios term, term_prev;
static struct winsize sz;
void
sigint(const int signo)
{
  tcsetattr(0, TCSANOW, &term_prev);
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

  // Get the LINE and COLS
  tcgetattr(0, &term_prev);
  term = term_prev;
  term.c_iflag &= ~(ICANON|ECHO|ECHONL);
  tcsetattr(0, TCSANOW, &term);

  ioctl(0, TIOCGWINSZ, &sz);
  
  printf("COLS: %d\n", sz.ws_col);
  printf("ROWS: %d\n", sz.ws_row);
 
  return EXIT_SUCCESS;
}
