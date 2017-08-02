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
	printf( "%d\n", x * y);
}

int main()
{ 
	object *o = malloc(sizeof(object));
	o->f = add;
	o->f(2, 4);
	return 0;
}


