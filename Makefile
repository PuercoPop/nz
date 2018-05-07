CC = gcc
INCS = -I. -I/usr/include
LIBS = -L/usr/lib -lreadline -lc
CFLAGS = -std=c99 -Wall -Werror -pedantic -D_XOPEN_SOURCE ${INCS}

m: m.c
	@$(CC) $(CFLAGS) m.c -o bin/$@ $(INCS)

p: p.c
	@$(CC) $(CFLAGS) p.c -o bin/$@ $(INCS)

pp: pp.c
	@$(CC) $(CFLAGS) pp.c -o bin/$@ $(INCS)

w: w.c
	@$(CC) $(CFLAGS) w.c -o bin/$@ $(INCS) $(LIBS)
