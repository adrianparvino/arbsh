#include "shared.h"

/*
	This program attempts to use the opaque-objects we have created.
	It has the ability to access and use the type "object" but not its
	structure members. The opaque object can only be manipulated via
	its API. Which in this case are the simple functions object_init ..
	and so on.
*/

int main(void)
{
	object *o;
	o = object_init(o);
	object_populate(o, "This is a string\n");
	object_write(o);
	object_free(o);

	//o->rp = "hello";  //<-- This will fail to compile if it is a truly opaque type,
			    // producing the error: "dereferencing pointer to incomplete
		            // type ‘object {aka struct object}" thus proving that the 
			    // implementation details are indeed hidden from the user of 
			    // the API. Uncomment it to verify
	return 0;
}
