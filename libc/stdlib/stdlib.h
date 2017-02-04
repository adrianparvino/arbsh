#include <sys/mman.h>
#define NALLOC 	10024 
#include "../stddef/stddef.h"
#include "../ctype/ctype.h"
#include "../string/string.h"

/* malloc */
union header {
	struct {
		union header	*ptr;  
		unsigned 	size;	
	} s;
	long x;
};

typedef union header Header; 

int gatoi(const char *);
double gatof(const char *);
void *gmalloc(size_t);
Header *morecore(unsigned);
void gfree(void *);
void *grealloc(void *, size_t);

/* bsearch */
struct tnode {
        char *word;
        int count;
        struct tnode *left;
        struct tnode *right;
};


struct tnode *addtree(struct tnode *, char *, int *);
void treefree(struct tnode *);



