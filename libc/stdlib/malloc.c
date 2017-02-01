#include "stdlib.h"

void* gmalloc(size_t nbytes) 
{
	Header *p, *prevp;		
	Header *morecore(unsigned);
	unsigned nunits; 

	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1; 

	if ((prevp = gfreep) == NULL) 
	{
		base.s.ptr = gfreep = prevp = &base;
		base.s.size = 0;	
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) 
	{
		if (p->s.size >= nunits)
		{
			if (p->s.size == nunits) 	
				prevp->s.ptr = p->s.ptr;
			else {			
				p->s.size -= nunits;
				p += p->s.size;		
				p->s.size = nunits;
			}
			gfreep = prevp;
			return (void*) (p+1);
		}
		if ( p == gfreep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}
