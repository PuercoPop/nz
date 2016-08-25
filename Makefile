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
	$(CC) $@.c $(CFLAGS) -o $@

test: read-integer read-symbol

read-integer: t/read-integer.c lisp.o
	$(CC) $(CFLAGS)  $^ -o bin/$@

read-symbol: t/read-symbol.c lisp.o
	$(CC) $(CFLAGS)  $^ -o bin/$@

clean:
	$(RM) $(OBJS)
