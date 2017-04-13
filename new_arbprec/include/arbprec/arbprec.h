#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _arbprec_h_
#define _arbprec_h_

/* Function protoypes */

int *addition(int *, int *, int *);	/* Add two arrays */
size_t arraylen(int *, int);		/* Similiar to strlen except it searches for the specified token */
void copyarray(int *, int *);		/* Copy an array of ints to another array of ints */ 
void die(char *);			/* Kill and error message */
int iszero(int *);			/* Returns true if an entire array is zero */ 
int *divide(int *, int *, int *);	/* Multiply arrays of integers (long multiplication) */ 
int *multiply(int *, int *, int *);	/* Multiply arrays of integers (long multiplication) */ 
size_t reversestr(int *);		/* Reverse an integer array */
void setarray(int *, int);		/* Set an array of ints to all zeros or a magnitude thereof */
int *subtraction(int *, int *, int *);	/* Subtract two arrays */

/* More (helper) function prototypes */
int *str2ints(char *, int *);		/* Convert a string into an integer array */ 
void printarray(int *, size_t len);	/* Print an array of integers */
int getcharval(int *, size_t);		/* Return an indice position if it exists, if not, return 0 */
void verbosity(int *, char *, int);	/* Verbosity function */
void *strallocate(size_t);		/* Memory allocater with error */

/* Globals */
extern size_t cardinal;			/* All array functions must have the same length (cardinality) */
extern int base; 			/* Default to base 10 */
int *mirror;
int *result;
int *tmpmir;

#endif /* _arbprec_h_ */

