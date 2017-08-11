#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

typedef struct{ 
        char rp[1024];
	size_t len;
} object; 

int main(void)
{ 
	size_t i = 0;
	size_t lim = 10;
	object p[10];
	object *o = p;

	for (o=p; i < lim ; ++i, ++o) 
		o->len = sprintf(o->rp, "string %zu\n", i);

	for (i=0, o=p; i < lim ; ++i, ++o)
		write(1, o->rp, o->len); 

	return 0; 
}

