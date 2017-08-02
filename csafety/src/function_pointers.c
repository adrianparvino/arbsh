/*
Function pointers make objects even more powerful by allowing them to have a
functions assigned as its various members. Effectively they take the struct 
which is data and the function (which has functionality) and combines them. Thus
allowing the object itself to perform actions.
*/

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 

typedef struct object object;

typedef struct object{ 
        char *rp;
	size_t len;
	object *(*f[10])(object *o); 
} object;

object *obj_init(object *o)
{
	o->rp = malloc(256);
	o->len = 0;
}

object *obj_pop(object *o)
{
	o->len = sprintf(o->rp, "%s\n", "string here");
}

object *obj_write(object *o)
{
	write(1, o->rp, o->len);
}

int main()
{ 
	object *o = malloc(sizeof(object));
	o->f[0] = obj_init; 
	o->f[1] = obj_pop; 
	o->f[2] = obj_write;

	o = o->f[0](o);
	o = o->f[1](o);
	o = o->f[2](o);


	return 0;
}


