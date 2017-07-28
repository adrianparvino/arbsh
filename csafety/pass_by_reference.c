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

void *safe_free3(void *a) 
{ 
	free(a); 
	return NULL; 
}

void safe_free2(void **a) 
{ 
	free(*a); 
	*a = NULL; 
}

void safe_free(void *a, void **b)
{ 
	free(a); 
	*b = NULL;
}

int main(void)
{
	char *l;
	c.rp = malloc(1000);
	safe_free(c.rp,(void**)&(c.rp));
	safe_free(c.rp,(void**)&(c.rp));
	safe_free(c.rp,(void**)&(c.rp));
	safe_free(c.rp,(void**)&(c.rp));

	d->rp = malloc(1000);
	safe_free(d->rp,(void**)&(d->rp));
        safe_free(d->rp,(void**)&(d->rp));
        safe_free(d->rp,(void**)&(d->rp));
        safe_free(d->rp,(void**)&(d->rp));

	l = malloc(1000);
	safe_free(l, (void**)&l);
	safe_free(l, (void**)&l);
	safe_free(l, (void**)&l);
	safe_free(l, (void**)&l);

	bb *ff;
	ff = malloc(sizeof(bb));
	ff->rp = malloc(1000); 
	safe_free(ff->rp, (void**)&(ff->rp));
	safe_free(ff->rp, (void**)&(ff->rp));
	safe_free(ff->rp, (void**)&(ff->rp));
	safe_free(ff->rp, (void**)&(ff->rp)); 
	safe_free(ff, (void**)&ff);
	safe_free(ff, (void**)&ff);
	safe_free(ff, (void**)&ff);

	c.rp = malloc(1000);
        safe_free2((void**)&(c.rp));
        safe_free2((void**)&(c.rp));
        safe_free2((void**)&(c.rp));
        safe_free2((void**)&(c.rp));

        d->rp = malloc(1000);
        safe_free2((void**)&(d->rp));
        safe_free2((void**)&(d->rp));
        safe_free2((void**)&(d->rp));
        safe_free2((void**)&(d->rp));

        l = malloc(1000);
        safe_free2((void**)&l);
        safe_free2((void**)&l);
        safe_free2((void**)&l);
        safe_free2((void**)&l);

       
        ff = malloc(sizeof(bb));
        ff->rp = malloc(1000);
        safe_free2((void**)&(ff->rp));
        safe_free2((void**)&(ff->rp));
        safe_free2((void**)&(ff->rp));
        safe_free2((void**)&(ff->rp));
        safe_free2((void**)&ff);
        safe_free2((void**)&ff);
        safe_free2((void**)&ff);


        ff = malloc(sizeof(bb));
        ff->rp = malloc(1000);

	ff->rp = safe_free3(ff->rp);
	ff->rp = safe_free3(ff->rp);
	ff->rp = safe_free3(ff->rp);
	ff->rp = safe_free3(ff->rp);
	
	return 0; 
}
