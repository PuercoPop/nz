CC = clang
LIBS =
CFLAGS = -Wall -Wpedantic -g -std=c11
LDFLAGS = -static ${LIBS}

SRCS = lisp.c
OBJS = $(SRCS:.c=.o)

all: nz lisp

%.o: %.c
	$(CC) $(CFLAGS) $< -c

nz: lisp.c
	$(CC) $@.c $(CCFLAGS) -o $@

test: read-integer

read-integer: t/read-integer.c lisp.o
	$(CC) $(CFLAGS)  $^ -o bin/$@

clean:
	$(RM) $(OBJS)
