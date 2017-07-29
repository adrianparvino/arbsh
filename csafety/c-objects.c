#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

typedef struct{ 
        char *rp; 
	size_t len;
} object; 

int main(void)
{ 
	size_t i = 0;
	size_t lim = 10;

	object *obja = malloc(sizeof(object) * lim); 

	for ( ; i < lim ; ++i)
	{
		(obja+i)->rp = malloc(sizeof(char) * 100);
		(obja+i)->len = sprintf((obja+i)->rp, "string %zu\n", i); 
	} 

	for (i=0 ; i < lim ; ++i)
		write(1, (obja+i)->rp, (obja+i)->len);

	for (i=0 ; i < lim ; ++i)
                free((obja+i)->rp);

	free(obja);
	return 0; 
}
