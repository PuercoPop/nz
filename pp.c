#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>

static struct termios term, term_prev;
static struct winsize sz;
static struct sigaction sa;
static int fd;

typedef struct Buffer {
    char *contents;
    size_t cur_size;
    size_t max_size;
    bool eof;
} Buffer;

static Buffer buf;

void setup();
void run();
void cleanup();
void die(char *, ...);
void init_buffer();
void grow_buffer();
void read_line();
void draw_page();

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
init_buffer()
{
    buf.contents = malloc(BUFSIZ);
    if (buf.contents == NULL)
        die("Could not allocate buffer.\n");
    buf.cur_size = 0;
    buf.max_size = BUFSIZ;
}

void
grow_buffer()
{
    char *tmp;
    buf.max_size *= 1.5;
    tmp = malloc(buf.max_size);
    if (tmp == NULL)
        die("Could not grow buffer.\n");
    memset(tmp, '\0', buf.max_size);

    memcpy(tmp, buf.contents, buf.cur_size - 1);
    free(buf.contents);
    buf.contents = tmp;
}

void
read_line()
{
    char next_char;
    int err;

    buf.eof = false;
    memset(buf.contents, '\0', buf.max_size);
    buf.cur_size = 0;

    for(;;) {
        err = read(fd, &next_char, 1);
        if (err < 0)
            perror("Could not read file.");

        if (err == 0) {
            buf.eof = true;
            break;
        }

        buf.contents[buf.cur_size] = next_char;
        buf.cur_size++;

        if (buf.cur_size > buf.max_size)
            grow_buffer();

        if (next_char == '\n') {
            break;
        }
    }
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

    init_buffer();
}

void
cleanup()
{
    tcsetattr(0, TCSANOW, &term_prev);
}

void
draw_page()
{
    for(size_t i = 0; i < sz.ws_row; i++) {
        read_line();
        write(0, buf.contents, buf.cur_size);
    }
    printf("Press m to continue"); // Print Header
}

int
main(int argc, char *argv[])
{
    if(argc < 2)
        die("Filename must be supplied.\n");
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        die("Could not open file: %s.\n");
    setup();

    ioctl(0, TIOCGWINSZ, &sz);
  
    printf("COLS: %d\n", sz.ws_col);
    printf("ROWS: %d\n", sz.ws_row);

    draw_page();
    
    cleanup();
    return EXIT_SUCCESS;
}
