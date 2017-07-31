#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shared.h"

int main(void)
{
	object *o;
	o = object_init(o);
	//o->rp = "hello";  //<--- This will fail if it is a truly opaque type
}
