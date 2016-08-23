/* Copyright 2016 Javier Olaechea

A 'MVP' lisp, only functions, symbols, integers and FFI

 */

#ifndef LISP_C
#define LISP_C

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lisp.h"

/* typedef enum { */
/*   EOF, */
/*   open_paren, */
/*   close_paren, */
/*   new_line, */
/*   quote, */
/*   symbol, */
/*   // number, // ? */
/* } tokename; */


// read.c
/* Read returns 0 on Sucess and the result?*/

/* LispObj* read(FILE *in) { */
/*   int c; */
/*   while ((c = getc(in)) != EOF) { */
/*     if (isspace(c)) { */
/*     } else */
/*       {} */
/*   } */
/*  error: */
/*   return -1; // or a 'Lisp Error' */
/* } */

/* Read the stream until a Space or End of File*/

/* NZ_Symbol* nz_read_symbol(FILE *in) { */
/*   int c; */
/*   while(1) { */
/*     c = getchar(c); */
/*     if isspace(c) { */
/*         break; */
/*       }; */
    
/*     if (isalphanum(c)) { */
/*     } */
      
/*       }; */
/*   make_symbol(string); */
/* } */

int nz_read_integer(FILE *in) {
  int c;
  int result = 0;
  while(1) {
    c = getc(in);

    if (!isdigit(c)) break;

    result *= 10;
    result += c - 48;
  }
  return result;
};

int main(int argc, char **argv) {
  // Test reading an expression and printing it.
  if (argc < 2) {
    printf("Missing filename to process\n");
    return -1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL) perror("Unable to open file");
  int i = nz_read_integer(f);
  printf("%i\n", i);

  return 1;
  
  // The REPL
  /* while(1) { */
  /*   write_lisp(eval(nz_read(stdin), NULL), stdout); */
  /*   putchar('\n'); */
  /*   fflush(stdout); */
  /* } */
  /* return 1; */
}

#endif
