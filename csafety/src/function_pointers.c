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

object *iterate(object *o);

typedef struct object{ 
        char *rp;
	size_t len;
	size_t actions;
	object *(*iterate)(object *o); 
	object *(*f[10])(object *o); 
} object;

object *obj_init(object *o)
{
	o->iterate = iterate;
	o->rp = malloc(256);
	o->len = 0;
	o->actions = 0;
}

object *obj_pop(object *o)
{
	o->len = sprintf(o->rp, "%s\n", "string here");
}

object *obj_write(object *o)
{
	write(1, o->rp, o->len);
}

object *obj_addaction(object *o, object *(*f)(object *))
{
	o->f[o->actions] = f;
	o->actions++;
	return o;
}


object *iterate(object *o)
{
	size_t i = 0;
	while ( i < o->actions)
	{
		o->f[i](o);
		++i;
	}
	return o;
}

int main()
{ 
	object *o = malloc(sizeof(object));
	o = obj_init(o);
	o = obj_addaction(o, obj_pop);
	o = obj_addaction(o, obj_write); 
	
	o = o->iterate(o);


	return 0;
}


