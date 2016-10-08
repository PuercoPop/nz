CC = clang
INCS = -I. -I/usr/include -I/usr/include/freetype2
LIBS = -L/usr/lib -lc -lX11 -lfontconfig -lXft
CFLAGS = -Wall -Wpedantic -g -std=c99 ${INCS}
LDFLAGS = ${LIBS}

CFLAGS +=  `pkg-config --cflags guile-2.0`
LIBS +=  `pkg-config --libs guile-2.0`
