/***
    Print the File but using iterator on a line per line basis.
 ***/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>

// FileBuffer
typedef struct Buffer {
  int descriptor;
  char char_buffer[BUFSIZ]
} Buffer;

struct Buffer buff;

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
setup(int argc, char *argv[])
{
    char *fpath = argv[1];
    int fd = open(fpath, O_RDONLY);
    if(fd < 0)
      die("Could not open file: %s.\n", fpath);

    buff.descriptor = fd;
}

char *
read_line(struct buffer)
{
  
}

int
main(int argc, char *argv[])
{
  if (argc < 2)
    die("Must provide a filename.\n");

  setup(argc, argv);

  /* char *line; */
  /* for(line = read_line(buffer); */
  /*     !(line == EOF); */
  /*     line = read_line(buffer)) */
               
    
  return EXIT_SUCCESS;
}
