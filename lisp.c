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
}

#endif
