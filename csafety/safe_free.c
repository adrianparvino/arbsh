#include <stdlib.h>
#include <stdio.h> 
/*
	
	The C11 draft states "If ptr is a null pointer, no action occurs."
	therefore preventing "double frees" is reduced to the simple
	operation of explicitly setting deallocated variables to NULL.  

*/

struct c { 
        char *rp; 
} c;

typedef struct{ 
        char *rp; 
} bb;

bb d[10]; 

void *safe_free(void *a) 
{ 
	free(a); 
	return NULL; 
}

int main(void)
{
	char *l; 
	bb *ff;
	ff = malloc(sizeof(bb));
	ff->rp = malloc(1000); 
	c.rp = malloc(1000); 
        l = malloc(1000);
	ff->rp = safe_free(ff->rp);
	ff->rp = safe_free(ff->rp);
	ff->rp = safe_free(ff->rp);
	ff->rp = safe_free(ff->rp);
	ff = safe_free(ff);
	ff = safe_free(ff);
	ff = safe_free(ff);
	ff = safe_free(ff);
	l = safe_free(l);
	l = safe_free(l);
	l = safe_free(l);
	c.rp = safe_free(c.rp);
	c.rp = safe_free(c.rp);
	c.rp = safe_free(c.rp);
	c.rp = safe_free(c.rp);
	
	return 0; 
}
