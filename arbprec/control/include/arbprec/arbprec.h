#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

/* defines */
#define ARBT char
#define UARBT unsigned char



/* globals */
extern int verbosity;

/* structures */
typedef struct {         
        ARBT *number;   
        int sign;      
        size_t lp;        
        size_t rp;       
        size_t len;       
        size_t allocated; 
        size_t chunk;    
} fxdpnt;

/* function prototypes */ 
fxdpnt *arb_expand(fxdpnt *, size_t);
fxdpnt *arb_str2fxdpnt(const char *);
fxdpnt *arb_alloc(size_t); 
void *arb_malloc(size_t);
void *arb_realloc(void *, size_t); 
void arb_init(fxdpnt *);
void arb_print(fxdpnt *);
void arb_free(fxdpnt *);
void arb_error(char *); 
int arb_highbase(int); 
fxdpnt *arb_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale); 
void arb_free(fxdpnt *flt);
fxdpnt *arb_new_num (int, int); 
fxdpnt *arb_divide(fxdpnt *, fxdpnt *, fxdpnt *, int, int); 
void short_multiply(unsigned char *, int, int, unsigned char *, int); 
void arb_free_num (fxdpnt *);









