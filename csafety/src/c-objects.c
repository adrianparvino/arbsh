/* 
*/

	#include <stdlib.h>
	#include <stdio.h> 
	#include <unistd.h>
	#include <stddef.h>

	typedef struct{ 
	        char *rp; 
		size_t len;
	} object; 

	int main(void)
	{
		ptrdiff_t lim = 10;
	
		/* create an "array" of objects */
		object *p, *o;
		if (!(o = p = malloc(sizeof(object) * lim)))
			return 1;

		/* allocate memory and populate "array" members */
		for (o=p; o-p < lim ; ++o)
		{
			if (!(o->rp = malloc(sizeof(char) * 100)))
				return 1;
			o->len = snprintf(o->rp, 100, "string %zu\n", o-p); 
		} 

		/* test the "array" of objects (fast write!) */
		for (o=p; o-p < lim ; ++o)
			write(1, o->rp, o->len);

		/* free the objects' member memory allocations */
		for (o=p; o-p < lim ; ++o)
	                free(o->rp);

		/* free the object */
		free(p);

		return 0; 
	}

