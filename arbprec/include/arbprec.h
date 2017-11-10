#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define TOYMT char
extern int verbosity;

typedef struct {          // Toym fixed point type
        char *number;     // The actual number
        int sign;         // Sign
        size_t lp;        // Length left of radix
        size_t rp;
        size_t len;       // Length of number (count of digits / limbs)
        size_t allocated; // Length of allocated memory
        size_t chunk;     // Allocation chunk size
} fxdpnt;

typedef struct {          // Toym floating point type
        char *number;
        int sign;
        size_t lp;
        size_t exp;       // Exponent
        size_t allocated;
} fltpnt;

#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))

fxdpnt *arb_div(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_mul(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_expand(fxdpnt *, size_t);
fxdpnt *arb_str2fxdpnt(const char *);
fxdpnt *arb_add_precision(fxdpnt *, size_t);
fxdpnt *arb_alloc(size_t);
fxdpnt *arb_div3(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base);
void *arb_malloc(size_t);
void *arb_realloc(void *, size_t);

void arb_reverse(char *, size_t);
void arb_flipsign(fxdpnt *);
void arb_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
void arb_init(fxdpnt *);
void arb_print(fxdpnt *);
void arb_free(fxdpnt *);
void arb_error(char *);


int arb_highbase(int);
int arb_place(fxdpnt *, fxdpnt *, size_t *, size_t);
int arb_compare(fxdpnt *a, fxdpnt *b, int base);
fxdpnt *arb_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale);
fxdpnt *arb_rightshift(fxdpnt *a, size_t n, int faux);
fxdpnt *arb_leftshift(fxdpnt *a, size_t n);


void arb_free(fxdpnt *flt);
fxdpnt *arb_new_num (int length, int scale);
void arb_free_num (fxdpnt *num);
fxdpnt *arb_divide(fxdpnt *n1, fxdpnt *n2, fxdpnt *quot, int base, int scale);
fxdpnt *arb_divide2(fxdpnt *n1, fxdpnt *n2, fxdpnt *quot, int base, int scale);
void arb_printold(fxdpnt *flt);

