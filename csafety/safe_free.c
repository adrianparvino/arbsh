#include <stdlib.h>
#include <stdio.h> 

struct c { 
        char *rp; 
} c;

typedef struct{ 
        char *rp; 
} bb;

bb d[10]; 

void safe_free2(void **a)
{ 
	free(*a); 
        *a = NULL;
	fprintf(stderr, "This function mysteriously prevents double frees\n");
}

void safe_free(void *a, void **b)
{
	if (a)
	{
		free(a);
		fprintf(stderr, "A true free was detected\n");
	}
	else {
		fprintf(stderr, "A double free was detected and prevented\n");
	}
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

	
	return 0; 
}
