#include "stdlib.h"

void *grealloc(void *old_ptr, size_t nbytes)
{
	Header *bp;
	void *new_ptr;
	size_t old_nbytes = 0;

	if (old_ptr == NULL)
		return gmalloc(nbytes);

	bp = (Header *) old_ptr - 1;
	
	old_nbytes = sizeof(Header) * (bp->s.size -1);
	
	if ((new_ptr = gmalloc(nbytes)) == NULL)
		return NULL;

	if (old_nbytes <= nbytes) 
		gmemcpy(new_ptr, old_ptr, old_nbytes);
	else
		gmemcpy(new_ptr, old_ptr, nbytes);
	
	gfree(old_ptr);
	return new_ptr;
}

