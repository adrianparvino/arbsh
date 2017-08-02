#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 

typedef struct{ 
        char *rp;
	size_t len;
	void (*f)(int, int);
} object;

void add(int x, int y)
{
	printf( "add %d\n", x + y);
}

void mul(int x, int y)
{
	printf( "mul %d\n", x * y);
} 

object *object_mathfunc(object *o, void (*func))
{
	o->f = func;
}

object *object_exec(object *o, int x, int y)
{
	o->f(x, y);
	return o;
}

int main()
{ 
	object *o = malloc(sizeof(object));
	o = object_mathfunc(o, add);
	o = object_exec(o, 2, 3);
	o = object_mathfunc(o, mul);
	o = object_exec(o, 2, 3);

	return 0;
}


