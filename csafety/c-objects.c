#include <stdlib.h>
#include <stdio.h> 

typedef struct{ 
        char *rp; 
} object; 

int main(void)
{ 
	object *obja = malloc(sizeof(object) * 10);
	object *hold = obja;
	size_t i = 0;

	for ( ; i < 10 ; ++i)
	{
		obja->rp = malloc(sizeof(char) * 100);
		sprintf(obja->rp, "string %zu\n", i); 
		++obja;
		
	}
	obja = hold;

	for (i=0 ; i < 10 ; ++i, ++obja)
		printf("%s", obja->rp);

	obja = hold;

	for (i=0 ; i < 10 ; ++i, ++obja)
                free(obja->rp);

	free(hold);
	return 0; 
}
