#ifndef ARBSH_ARBPREC_H
#define ARBSH_ARBPREC_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

/* defines */
#define ARBT char	// designed to be any type
#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))

/* structures */
typedef struct {	// fxdpnt fixed point type
	ARBT *number;	// The actual number
	char sign;	// Sign
	size_t lp;	// Length left of radix
	size_t len;	// Length of number (count of digits / limbs)
	size_t allocated;// Length of allocated memory
} fxdpnt;

/* function prototypes */
/* arithmetic */
fxdpnt *arb_mul(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
fxdpnt *arb_exp(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
size_t arb_mul_core(ARBT *, size_t, ARBT *, size_t, ARBT *, int);
fxdpnt *arb_karatsuba_mul(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_karatsuba_mul2(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
fxdpnt *arb_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add(fxdpnt *, fxdpnt *, fxdpnt *, int);

fxdpnt *arb_sub2(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add2(fxdpnt *, fxdpnt *, fxdpnt *, int);
ARBT arb_place(fxdpnt *, fxdpnt *, size_t *, size_t);
fxdpnt *arb_newtonian_div(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_alg_d(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
int _long_sub(ARBT *, size_t, ARBT *, size_t, int);
int _long_add(ARBT *, size_t, ARBT *, size_t, int);
fxdpnt *arb_mod(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
/* logical shift */
fxdpnt *arb_rightshift(fxdpnt *, size_t, int);
fxdpnt *arb_leftshift(fxdpnt *, size_t, int);
void rightshift_core(ARBT *, size_t, size_t);
/* general */
//void arb_reverse(ARBT *, size_t);
void arb_reverse(fxdpnt *);
void arb_flipsign(fxdpnt *);
void arb_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
/* io */
void arb_print(fxdpnt *);
void _print_core(FILE *, ARBT *, size_t, size_t, size_t, int);
fxdpnt *arb_str2fxdpnt(const char *);
fxdpnt *arb_parse_str(fxdpnt *, const char *);
int arb_highbase(int);
/* comparison */
int arb_compare(fxdpnt *, fxdpnt *, int);
/* copying */
void _arb_copy_core(ARBT *, ARBT *, size_t);
void arb_copy(fxdpnt *, fxdpnt *);
void arb_copyreverse(fxdpnt *, fxdpnt *);
/* sqrt */
fxdpnt *arb_newton_sqrt(fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_long_sqrt(fxdpnt *, fxdpnt *, int, int);
/* general */
void arb_init(fxdpnt *);
fxdpnt *arb_construct(fxdpnt *, size_t);
void arb_error(char *);
/* allocation */
fxdpnt *arb_alloc(size_t);
fxdpnt *arb_expand(fxdpnt *, size_t);
fxdpnt *arb_expand2(fxdpnt *, size_t);
fxdpnt *arb_expand_nozero(fxdpnt *, size_t);
void *arb_malloc(size_t);
void *arb_realloc(void *, size_t);
void *arb_calloc(size_t, size_t);
void arb_free(fxdpnt *);
void arb_destruct(fxdpnt *);
/* base conversion */
fxdpnt *convert(fxdpnt *, fxdpnt *, int, int);
fxdpnt *conv_frac(fxdpnt *, fxdpnt *, int, int);
ARBT arb2hrdware(ARBT *, size_t, int);
fxdpnt *hrdware2arb(size_t);
void hrdware2arb2(fxdpnt **num, int val, int);
//fxdpnt *hrdware2arb2(fxdpnt *num, int val);
fxdpnt *convall(fxdpnt *, fxdpnt *, int, int);
fxdpnt *convscaled(fxdpnt *, fxdpnt *, int, int);
fxdpnt *remove_leading_zeros(fxdpnt *);
fxdpnt *arb_exp(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
fxdpnt *arb_exp2(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);

size_t rr(fxdpnt*);
int iszero(fxdpnt*);
size_t fxd2sizet(fxdpnt *, int);
#endif

