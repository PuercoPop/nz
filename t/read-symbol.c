#include <assert.h>
#include <string.h>
#include "../lisp.h"

int
main(int argc, char **argv)
{
  FILE *f = fopen("t/symbol.nz", "r");
  if (f == NULL)
    perror("Unable to open file: symbol.nz");

  char *symbol = nz_read_symbol(f);
  printf("Read symbol: %s\n", symbol);
  assert(strncmp("foo", symbol, MAX_SYMBOL_LENGTH));
  return 1;
}
