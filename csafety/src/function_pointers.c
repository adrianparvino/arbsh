/*
Function pointers make objects even more powerful by allowing them to have a
functions assigned as its various members. Effectively they take the struct 
which is data and the function (which has functionality) and combines them. Thus
allowing the object itself to perform actions.
*/

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 

typedef struct{ 
        char *rp;
	size_t len;
	int (*f)(int, int);
} object;

int add(int x, int y)
{
	return x+y;
}

int mul(int x, int y)
{
	return x*y;
}

object *object_init(object *o, int (*func)(int x, int y))
{
	o->f = func;
	return o;
}

object *object_exec(object *o, int x, int y)
{ 
	printf( "%d\n",  o->f(x, y));
	return o;
}

int main()
{ 
	object *o = malloc(sizeof(object));

	o = object_init(o, add);

	o = object_exec(o, 2, 3);

	o = object_init(o, mul);

	o = object_exec(o, 2, 3);

		/* or */

	printf( "%d\n",  o->f(3, 3));

	free(o);

	return 0;
}


