CFLAGS = -Wall

nz: lisp.c
	$(CC) $(CFLAGS) lisp.c -o nz
