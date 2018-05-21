/***
    Print the File but using iterator on a line per line basis.
 ***/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int in;

// FileBuffer
typedef struct Buffer {
    char *contents;
    size_t curr_size;
    size_t max_size;
    bool eof;
} Buffer;

struct Buffer buf;

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
    in = open(fpath, O_RDONLY);
    if(in < 0)
      die("Could not open file: %s.\n", fpath);

    buf.contents = malloc(BUFSIZ);
    if (buf.contents == NULL) {
        die("Could not allocate buffer memory");
    }
    buf.curr_size = 0;
    buf.max_size = BUFSIZ;
}

void
read_line(Buffer buff)
{
    char next_char;
    int err;

    buf.eof = false;
    memset(buf.contents, '\0', buf.max_size);
    buf.curr_size = 0;
    for(;;) {
        err = read(in, &next_char, 1);
        if (err < 0)
            perror("error reading file");

        if (err == 0) {
            buf.eof = true;
            break;
        }
        
        buf.contents[buf.curr_size] = next_char;
        if(next_char == '\n' ) {
            break;
        }

        buf.curr_size++;

        if (buf.curr_size > buf.max_size) {
            char *tmp;
            buf.max_size *= 1.5;
            tmp = malloc(buf.max_size);
            if (tmp == NULL)
                die("Could not grow buffer");
            memset(tmp, '\0', buf.max_size);

            memcpy(tmp, buf.contents, buf.curr_size - 1);
            buf.contents = tmp;
        }
    }
}

int
main(int argc, char *argv[])
{
  if (argc < 2)
    die("Must provide a filename.\n");

  setup(argc, argv);

  for(read_line(buf);
      !(buf.eof);
      read_line(buf))
  {
      printf("%s", buf.contents);
  }
  printf("%s\n", buf.contents);

  return EXIT_SUCCESS;
}
