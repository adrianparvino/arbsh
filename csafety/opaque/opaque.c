#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
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
	o->len = 0;
	return o;
}

object *object_populate(object *o, char *s)
{
	o->rp = s;
	o->len = strlen(s);
}

void object_free(object *o)
{ 
	free(o);
}

void object_write(object *o)
{
	write(1, o->rp, o->len);
}


