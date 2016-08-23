#include <assert.h>
#include "../lisp.h"

/* Stub test suite */

int
main(int argc, char **argv) {
  FILE *f = fopen("t/integer.nz", "r");
  if (f == NULL)
    perror("Unable to open file: integer.nz");

  int i = nz_read_integer(f);

  assert(i == 123);
}
