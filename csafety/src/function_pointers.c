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

void *safe_free(void *a)
{
        free(a);
        return NULL;
}

void *verbose_malloc(size_t i)
{
        void *ret;
        if (!(ret = malloc(i)))
                perror("malloc error: ");
        return ret;
}

object *obj_init(object *o)
{
	o->iterate = iterate; 
	o->rp = NULL;
	o->len = 0;
	o->actions = 0;
	if (!(o->rp = verbose_malloc(256)))
		return NULL;
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
	o->rp =	safe_free(o->rp);
	return o;
}

int main(void)
{ 
	object *o, *p;
	ptrdiff_t lim = 10;

	if (!(o = p = verbose_malloc(sizeof(object) * lim)))
		return 1;

	for(o=p; o-p < lim;++o)
	{
		o = obj_init(o);
		o = obj_addaction(o, obj_pop);
		o = obj_addaction(o, obj_write);
		o = obj_addaction(o, obj_free);
		o = o->iterate(o);
	}
	free(p);
	return 0;
}



