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

fxdpnt *toym_div(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_mul(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_sub(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_expand(fxdpnt *, size_t);
fxdpnt *toym_str2fxdpnt(const char *);
fxdpnt *toym_add_precision(fxdpnt *, size_t);
fxdpnt *toym_alloc(size_t);
fxdpnt *toym_div3(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base);
void *toym_malloc(size_t);
void *toym_realloc(void *, size_t);

void toym_reverse(char *, size_t);
void toym_flipsign(fxdpnt *);
void toym_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
void toym_init(fxdpnt *);
void toym_print(fxdpnt *);
void toym_free(fxdpnt *);
void toym_error(char *);


int toym_highbase(int);
int toym_place(fxdpnt *, fxdpnt *, size_t *, size_t);
int toym_compare(fxdpnt *a, fxdpnt *b, int base);
fxdpnt *toym_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale);
fxdpnt *toym_rightshift(fxdpnt *a, size_t n, int faux);
fxdpnt *toym_leftshift(fxdpnt *a, size_t n);


void toym_free(fxdpnt *flt);
fxdpnt *toym_new_num (int length, int scale);
void toym_free_num (fxdpnt *num);
fxdpnt *toym_divide(fxdpnt *n1, fxdpnt *n2, fxdpnt *quot, int base, int scale);
fxdpnt *toym_divide2(fxdpnt *n1, fxdpnt *n2, fxdpnt *quot, int base, int scale);
void toym_printold(fxdpnt *flt);

