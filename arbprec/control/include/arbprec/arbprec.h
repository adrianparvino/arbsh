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
fxdpnt *ccarb_expand(fxdpnt *, size_t);
fxdpnt *ccarb_str2fxdpnt(const char *);
fxdpnt *ccarb_alloc(size_t); 
void *ccarb_malloc(size_t);
void *ccarb_realloc(void *, size_t); 
void ccarb_init(fxdpnt *);
void ccarb_print(fxdpnt *);
void ccarb_free(fxdpnt *);
void ccarb_error(char *); 
int ccarb_highbase(int); 
fxdpnt *ccarb_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale); 
void ccarb_free(fxdpnt *flt);
fxdpnt *ccarb_new_num (int, int); 
fxdpnt *ccarb_divide(fxdpnt *, fxdpnt *, fxdpnt *, int, int); 
void short_multiply(unsigned char *, int, int, unsigned char *, int); 
void ccarb_free_num (fxdpnt *);









