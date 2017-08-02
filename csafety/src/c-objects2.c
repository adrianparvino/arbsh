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
	object o[10]; 

	for ( ; i < lim ; ++i) 
		(o+i)->len = sprintf((o+i)->rp, "string %zu\n", i); 

	for (i=0 ; i < lim ; ++i)
		write(1, (o+i)->rp, (o+i)->len); 

	return 0; 
}

