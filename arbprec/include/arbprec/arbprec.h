#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Macros */
#define MAX(a,b) ((a) > (b) ? a : b)

/* Structures and type definitions */
typedef struct {		/*     bigflt type		*/
	int *number;		/* Main number			*/
	int *mirror;		/* Negative subtraction requires a mirror */
	int sign;		/* Sign 			*/
	size_t float_pos;	/* Length left of radix 	*/
	size_t len;		/* Length of number 		*/
	size_t allocated;	/* Length of allocated memory 	*/
	size_t chunk;		/* Allocation chunk size 	*/
	int nan;		/* Not a number			*/
	int inf;		/* Infinity 			*/
} bigflt;

/* Function protoypes */
bigflt *arbprec_add(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_add_inter(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_copy(bigflt *, bigflt *);
bigflt *arbprec_div(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_dupa(bigflt *);
bigflt *arbprec_expand_vector(bigflt *, size_t);
bigflt *arbprec_init(bigflt *);
bigflt *arbprec_initsign(bigflt *);
bigflt *arbprec_print(bigflt *);
bigflt *arbprec_mul(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_setsign(bigflt *);
bigflt *arbprec_sub(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_sub_inter(bigflt *, bigflt *, bigflt *);
bigflt *str_to_bigflt(const char *);
bigflt *arbprec_dup_sparse_mirror(bigflt *);
bigflt *arbprec_sqrt(bigflt *, bigflt *);
bigflt *arbprec_hypot(bigflt *, bigflt *, bigflt *);
bigflt *arbprec_series(bigflt *, bigflt *, int);
bigflt *arbprec_exp(bigflt *, bigflt *);
bigflt *arbprec_log(bigflt *, bigflt *);
bigflt *arbprec_sin(bigflt *, bigflt *);
bigflt *arbprec_cos(bigflt *, bigflt *);
bigflt *arbprec_tan(bigflt *, bigflt *);
bigflt *arbprec_add_precision(bigflt *, size_t);
bigflt *arbprec_sqrt_longhand(bigflt *, bigflt *);
bigflt *arba_alloc(size_t);
bigflt *strip_zeros(bigflt *);
bigflt *arbprec_copy_info(bigflt *, bigflt *);

void arbprec_short_add(bigflt *, int);
void arbprec_short_sub(bigflt *, int);
void arbprec_short_mul(bigflt *, int);
void arbprec_short_div(bigflt *, int);
bigflt *arbprec_short_add_r(bigflt *, int, bigflt *);
bigflt *arbprec_short_sub_r(bigflt *, int, bigflt *);
bigflt *arbprec_short_mul_r(bigflt *, int, bigflt *);
bigflt *arbprec_short_div_r(bigflt *, int, bigflt *);

int arbprec_isnegati(bigflt *);
void arbprec_match_precision(bigflt *, bigflt*);
void arba_free(bigflt *);
void arbprec_die(char *);
void *arbprec_malloc(size_t);
void *arbprec_realloc(void *, size_t);
void arbprec_reverse(int *, size_t);
void copyarray(int *, int *, size_t);
int place(bigflt *, size_t);
int iszero(int *, size_t);
void setarray(int *, int, size_t);
size_t rr(bigflt *);
size_t rl(bigflt *);
size_t rsh(bigflt *);
int arbprec_compare(bigflt *, bigflt *);

/* Globals */
extern int base;
extern size_t scale;


