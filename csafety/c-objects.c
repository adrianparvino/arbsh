#include <stdlib.h>
#include <stdio.h> 

typedef struct{ 
        char *rp; 
} object; 

int main(void)
{ 
	object *obja = malloc(sizeof(object) * 10);

	size_t i = 0;

	for ( ; i < 10 ; ++i)
	{
		(obja+i)->rp = malloc(sizeof(char) * 100);
		sprintf((obja + i)->rp, "string %zu\n", i); 
	} 

	for (i=0 ; i < 10 ; ++i)
		printf("%s", (obja+i)->rp); 

	for (i=0 ; i < 10 ; ++i)
                free((obja+i)->rp);

	free(obja);
	return 0; 
}
