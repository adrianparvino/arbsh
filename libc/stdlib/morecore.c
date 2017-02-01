#include "stdlib.h"
Header *morecore(unsigned nu)
{
	char *cp;
	void gfree(void*);
	Header *up;
	if (nu < NALLOC)
		nu = NALLOC;
	/* cp = sbrk(nu * sizeof(Header)); */
	cp = mmap( 0, nu* sizeof(Header), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
	if (cp == (char *) -1)
		return NULL;
	up = (Header*) cp;
	up->s.size = nu;
	gfree((void*)(up+1));
	return gfreep;
}
