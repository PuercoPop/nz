#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>

static struct termios term, term_prev;
static struct winsize sz;
static struct sigaction sa;

void cleanup();

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
  cleanup();
  exit(0);
}

void
setup()
{
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = sigint;
  if(sigaction(SIGINT, &sa, NULL))
    die("Could not setup sigterm handler\n");

  tcgetattr(0, &term_prev);
  term = term_prev;
  term.c_iflag &= ~(ICANON|ECHO|ECHONL);
  tcsetattr(0, TCSANOW, &term);
}

void
cleanup()
{
  tcsetattr(0, TCSANOW, &term_prev);
}

int
main(int argc, char *argv[])
{
  setup();

  ioctl(0, TIOCGWINSZ, &sz);
  
  printf("COLS: %d\n", sz.ws_col);
  printf("ROWS: %d\n", sz.ws_row);

  cleanup();
  return EXIT_SUCCESS;
}
