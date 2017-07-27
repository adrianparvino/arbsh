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
		printf("A true free was detected\n"); 
		free(a);
	}
	else {
		printf("A double free was detected\n"); 
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
	return 0; 
}
