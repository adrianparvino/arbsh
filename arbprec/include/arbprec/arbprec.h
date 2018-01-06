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
typedef struct {	// Toym fixed point type
	ARBT *number;	// The actual number
	char sign;	// Sign
	size_t lp;	// Length left of radix
	size_t rp;	// Length right of radix
	size_t len;	// Length of number (count of digits / limbs)
	size_t allocated;// Length of allocated memory
	size_t chunk;	// Allocation chunk size (just avoids globals)
} fxdpnt;

/* function prototypes */
/* arithmetic */
fxdpnt *arb_mul(fxdpnt *, fxdpnt *, fxdpnt *, int);
size_t arb_mul_core(ARBT *, size_t, ARBT *, size_t, ARBT *, int);
fxdpnt *arb_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
ARBT arb_place(fxdpnt *, fxdpnt *, size_t *, size_t);
fxdpnt *arb_newtonian_div(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_alg_d(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
int _long_sub(ARBT *, size_t, ARBT *, size_t, int);
int _long_add(ARBT *, size_t, ARBT *, size_t, int);
/* logical shift */
fxdpnt *arb_rightshift(fxdpnt *, size_t, int);
fxdpnt *arb_leftshift(fxdpnt *, size_t, int);
void arb_reverse(ARBT *, size_t);
void arb_flipsign(fxdpnt *);
void arb_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
/* io */
void arb_print(fxdpnt *);
void _print_core(FILE *, ARBT *, size_t, size_t, size_t);
fxdpnt *arb_str2fxdpnt(const char *);
int arb_highbase(int);
/* comparison */
int arb_compare(fxdpnt *, fxdpnt *, int);
/* copying */
void _arb_copy_core(ARBT *, ARBT *, size_t);
void arb_copy(fxdpnt *, fxdpnt *);
/* sqrt */
fxdpnt *arb_babylonian_sqrt(fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_newton_sqrt(fxdpnt *, fxdpnt *, int, int);
/* general */
void arb_init(fxdpnt *);
void arb_error(char *);
/* allocation */
fxdpnt *arb_alloc(size_t);
fxdpnt *arb_expand(fxdpnt *, size_t);
void *arb_malloc(size_t);
void *arb_realloc(void *, size_t);
void *arb_calloc(size_t, size_t);
void arb_free(fxdpnt *);
/* min / max */
size_t maxi(size_t, size_t, size_t);
/* base conversion */
fxdpnt *convert(fxdpnt *, fxdpnt *, int, int);

//void convert_radix(ARBT *array, size_t len, int value, int ibase, int obase);
//void arb_short_mul(ARBT *a, size_t i, int b, int base);

void rightshift_core(ARBT *, size_t, size_t);
