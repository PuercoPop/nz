#ifndef LISP_H
#define LISP_H

#include <stdio.h>


// Types.h
typedef struct LispObj {
} LispObj;

enum {
  Symbol, NZ_Int;
}

typedef struct Symbol {
  char* name;
};



// Read.h
LispObj* nz_read(FILE*);
int read_symbol(FILE*);
int read_number(FILE*);

#endif
