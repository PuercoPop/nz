#ifndef LISP_H
#define LISP_H

#include <stdio.h>


// Types.h
typedef struct LispObj {
} LispObj;

enum {
  Symbol, NZ_Int;
}
#define MAX_SYMBOL_LENGTH 100

typedef struct Symbol {
typedef struct NZ_Symbol {
  char* name;
} NZ_Symbol;



// Symbols.h
NZ_Symbol make_symbol(char *);


// Read.h
LispObj* nz_read(FILE*);
int read_symbol(FILE*);
int read_number(FILE*);
char* nz_read_symbol(FILE*);
int nz_read_integer(FILE*);

#endif
