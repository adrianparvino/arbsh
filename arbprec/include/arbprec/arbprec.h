#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef _arbprec_h_
#define _arbprec_h_

/* Macros */
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

/* Structures and type definitions */ 

/*
	radix_right = len - ( len - float_pos );
	radix_left  = len - float_pos;
*/

typedef struct {		/*     bigflt type		*/
	int *number;		/* Main number			*/
	int *mirror;		/* Negative subtraction requires a mirror */
	int *nr;		/* Garbage collection for number */
	int *mr;		/* Garbage collction for mirror */
	int sign;		/* Sign 			*/
	size_t float_pos;	/* Length left of radix 	*/
	size_t len;		/* Length of number 		*/
	size_t allocated;	/* Length of alocated memory 	*/
	size_t chunk;		/* Allocation chunk size 	*/
	int nan;		/* Not a number			*/
	int inf;		/* Infinity 			*/
} bigflt;

/* Function protoypes */
bigflt *arbprec_add(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_add_inter(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_copy(bigflt *, bigflt *);
bigflt *arbprec_copy_sparse(bigflt *, bigflt *);
bigflt *arbprec_div(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_dupa(bigflt *);
bigflt *arbprec_dup_sparse(bigflt *);
bigflt *arbprec_expand_vector(bigflt *, size_t);

bigflt *arbprec_init(bigflt *);
bigflt *arbprec_initsign(bigflt *);
bigflt *arbprec_print(bigflt *);
bigflt *arbprec_print_simple(bigflt *);
bigflt *arbprec_mul(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_setsign(bigflt *);
bigflt *arbprec_sub(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_sub_inter(bigflt *, bigflt *, bigflt *);
bigflt *str_to_bigflt(const char *);

bigflt *arbprec_dup_sparse_mirror(bigflt *);


bigflt *arbprec_sqrt(bigflt *);
bigflt *arbprec_hypot(bigflt *, bigflt *);

bigflt *arbprec_sin(bigflt *);


void arbprec_match_precision(bigflt *, bigflt*);
bigflt *arbprec_add_precision(bigflt *, size_t);

/* internal function prototypes */
bigflt *arba_alloc(size_t);
void arbprec_die(char *);
int arbprec_isnegati(bigflt *);
void *arbprec_malloc(size_t);
void *arbprec_realloc(void *, size_t);
void arbprec_reverse(int *, size_t);
void copyarray(int *, int *, size_t);
int hasplace(int *, size_t, size_t);		/* Return an indice position if it exists, if not, return 0 */
int iszero(int *, size_t);
void setarray(int *, int, size_t);
void arba_free(bigflt *);

size_t rr(bigflt *);
size_t rl(bigflt *);
void rst(bigflt *, size_t);
size_t rsh(bigflt *);
size_t arbprec_balance_sum(bigflt *, bigflt *, bigflt *, size_t);

/* Globals */
extern int base; 				/* Default to base 10 */
extern size_t scale;

#endif /* _arbprec_h_ */

