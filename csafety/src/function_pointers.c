/*
The concept of function pointers can be extended to an array of function
pointers within an object. By also including an "iterator" function we can
effectively add functions into the array one at a time and then execute them
all at once with the iterator function. The initializer function is left
seperate and functions are added with the obj_addaction function.

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
	if (o->rp == NULL)	

	if (!(o->rp = malloc(256)))
		return NULL;
	o->len = 0;
	o->actions = 0;
	return o;
}

object *obj_pop(object *o)
{
	o->len = sprintf(o->rp, "%s\n", "string here");
	return o;
}

object *obj_write(object *o)
{
	write(1, o->rp, o->len);
	return o;
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
	for (; i < o->actions;++i) 
		o = o->f[i](o);
	return o;
}

object *obj_free(object *o)
{
	free(o->rp);
	o->rp = NULL;
	return o;
}

int main(void)
{ 
	object *o;
	object *p;
	size_t set = 30;
	size_t i = 0;

	if(!(p = malloc(sizeof(object) * set)))
		return 1;

	for(o = p;o-p<set;++o)
	{
		o = obj_init(o);
		o = obj_addaction(o, obj_pop);
		o = obj_addaction(o, obj_write);
		o = obj_addaction(o, obj_free);
		o = o->iterate(o);
	} 
	free(o = p);
	return 0;
}



