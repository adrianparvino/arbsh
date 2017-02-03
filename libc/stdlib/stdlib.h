//#include <ctype.h>
#include <sys/mman.h> 
#include <sys/syscall.h>
#define NALLOC 	10024 
#include "../stddef/stddef.h"
#include "ctype.h"
#include "string.h"

/* structures */
union header {
	struct {
		union header	*ptr;  
		unsigned 	size;	
	} s;
	long x;
};

typedef union header Header;
//static Header base;
//static Header *gfreep = NULL;

/* function prototypes */ 
int gatoi(const char *);
double gatof(const char *);
void *gmalloc(size_t);
Header *morecore(unsigned);
void gfree(void *);
void *grealloc(void *, size_t);
