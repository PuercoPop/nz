#include "lisp.h"

int
main(int argc, char *argv[]) {
  while(1) {
    nz_print(nz_eval(nz_read(stdin), NULL), stdout);
    putchar('\n');
    fflush(stdout);
  }
  return 1;
}
