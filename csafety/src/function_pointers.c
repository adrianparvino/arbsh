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
	object *next;
	object *(*a)(object *o);
	object *(*b)(object *o);
	object *(*c)(object *o);
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
	o->a = obj_init; 
	o->b = obj_pop; 
	o->c = obj_write;

	o = o->a(o);
	o = o->b(o);
	o = o->c(o);


	return 0;
}


