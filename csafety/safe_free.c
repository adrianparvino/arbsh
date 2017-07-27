#include <stdlib.h>
#include <stdio.h> 

struct c { 
        char *rp; 
} c;

typedef struct{ 
        char *rp; 
} bb;

bb d[10]; 

void safe_free(void *a, void **b)
{ 
	if (a != 0)
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

	char *l = malloc(1000); 
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
	safe_free(ff->rp, (void**)&(ff->rp));
	safe_free(ff, (void**)&ff);
	safe_free(ff, (void**)&ff);
	safe_free(ff, (void**)&ff);
	safe_free(ff, (void**)&ff);
	

	return 0; 
}
