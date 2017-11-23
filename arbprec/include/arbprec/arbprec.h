#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

/* defines */
#define ARBT char // designed to be any type
#define LARBT int
#define UARBT unsigned char
#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))

/* globals */
extern int verbosity;

/* structures */
typedef struct {          // Toym fixed point type
        ARBT *number;     // The actual number
        char sign;        // Sign
        size_t lp;        // Length left of radix
        size_t rp;        // Length right of radix
        size_t len;       // Length of number (count of digits / limbs)
        size_t allocated; // Length of allocated memory
        size_t chunk;     // Allocation chunk size (just avoids globals)
} fxdpnt;

/* function prototypes */
fxdpnt *arb_div(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_mul(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_expand(fxdpnt *, size_t);
fxdpnt *arb_str2fxdpnt(const char *);
fxdpnt *arb_alloc(size_t);
fxdpnt *arb_division(fxdpnt *, fxdpnt *, fxdpnt *c, int, int);
fxdpnt *arb_rightshift(fxdpnt *, size_t, int);
fxdpnt *arb_leftshift(fxdpnt *, size_t, int);
fxdpnt *arb_divide(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_divide2(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_newtonian_div(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_alg_d(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
void *arb_malloc(size_t);
void *arb_realloc(void *, size_t);
void arb_reverse(ARBT *, size_t);
void arb_flipsign(fxdpnt *);
void arb_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
void arb_init(fxdpnt *);
void arb_print(fxdpnt *);
void arb_free(fxdpnt *);
void arb_error(char *);
size_t rl(fxdpnt *);
int arb_highbase(int);
int arb_place(fxdpnt *, fxdpnt *, size_t *, size_t);
int arb_compare(fxdpnt *, fxdpnt *, int);
void arb_free(fxdpnt *);
void arb_free_num (fxdpnt *num);
void arb_printold(fxdpnt *);
void arb_mul_core(ARBT *, size_t, ARBT *, size_t, ARBT *, int);
void _print_core(FILE *, ARBT *, size_t, size_t);
fxdpnt *ccarb_divide(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_babylonian_sqrt(fxdpnt *x, fxdpnt *c, int base, int scale);
