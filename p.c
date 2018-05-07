#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void
die(char *msg, ...)
{
  va_list ap;

  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  exit(1);
}

int
main(int argc, char *argv[])
{
  if (argc < 2)
    die("Must supply filename.\n");

  char *fpath = argv[1];

  int fd = open(fpath, O_RDONLY);
  if (fd < 0)
    die("Could not open file: %s\n", fpath);

  char buf[BUFSIZ];

  int len;
  for(len = read(fd, buf, BUFSIZ);
      len > 0;
      len = read(fd, buf, BUFSIZ))
  {
    write(1, buf, len);
  }
  printf("len: %d", len);

  close(fd);
  
  return EXIT_SUCCESS;
}
