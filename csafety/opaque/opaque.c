#include <stdlib.h>
#include "shared.h"

struct object {
	char *rp;
	size_t len;
}; 

size_t object_size(void)
{
	return sizeof(object);
}

object *object_init(object *o)
{
	o = malloc (object_size());
	o->rp = malloc(1000);
	o->len = 0;
	return o;
}





