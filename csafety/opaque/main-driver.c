#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shared.h"

int main(void)
{
	object *o;
	o = object_init(o);
	object_populate(o, "This is a string\n");
	object_write(o); 

	//o->rp = "hello";  //<--- This will fail if it is a truly opaque type
	return 0;
}
