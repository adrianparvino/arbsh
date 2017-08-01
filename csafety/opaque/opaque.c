#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shared.h"

/*
	This is the actual opaque API library implementation. We declare an
	instantiation of the primary API structure from "shared.h" our shared
	header. But in this version we actually define its members. Inside of
	this file we can access all of the members of our opaque type but the
	end user of the API, or indeed anyone outside of this file can not.
	However, they can use the library as a library of opaque objects. The
	canonical example of the opaque object in C is the FILE * structure
	from stdio.  
*/

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


