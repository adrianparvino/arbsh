#include <stdlib.h>
#include <stdio.h> 
/* 
The C11 draft states "If ptr is a null pointer, no action occurs."
therefore preventing "double frees" is reduced to the simple
operation of explicitly setting deallocated variables to NULL.
*/


typedef struct{ 
        char *rp; 
	size_t len;
}object;

void *safe_free(void *a) 
{ 
	free(a); 
	return NULL; 
}

int main(void)
{ 
	object *o;
	if(!(o = malloc(sizeof(object))))
		return 1;
	o->rp = malloc(1000); 
	o->rp = safe_free(o->rp);
	o->rp = safe_free(o->rp); // does nothing
	o = safe_free(o);
	o = safe_free(o); // does nothing
	return 0; 
}
