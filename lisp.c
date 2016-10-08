/* Copyright 2016 Javier Olaechea

A 'MVP' lisp, only functions, symbols, integers, and FFI. We should probably
 include strings.

 */

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

static char buf[MAX_SYMBOL_LENGTH]; // For reading symbols

NZ_Symbol
make_symbol(char *symbol_name)
{
  NZ_Symbol sym;
  sym.name = symbol_name;
  return sym;
}

// NZ_Symbol*
char *
nz_read_symbol(FILE *in) {
  /* Read up to 10 chars before rellocating the string */
  int c;
  size_t currentBufferLength = 0;

  while(1) {
    c = getc(in);
    if (c == EOF)
      perror("Unexpected EOF");
    
    if isspace(c) {
        buf[currentBufferLength] = '\0';
        return buf;
        // return make_symbol(buf);
        break;
      };
    
    if (!isalnum(c))
      perror("Unrecognized Character");

    buf[currentBufferLength] = c;
    currentBufferLength++;
    if (currentBufferLength == MAX_SYMBOL_LENGTH)
      perror("Exceeded Max symbol length");
  };
  // make_symbol(string);
}

int
nz_read_integer(FILE *in) {
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
