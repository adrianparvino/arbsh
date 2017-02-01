#include "stdlib.h"


void gfree(void *ap) 
{
	Header *bp, *p;
    
	bp = (Header*) ap - 1;		

	for (p = gfreep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	if (bp + bp->s.size == p->s.ptr) 
	{
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
		bp->s.ptr = p->s.ptr;
		if ( p + p->s.size == bp ) 
		{

			p->s.size += bp->s.size;
			p->s.ptr = bp->s.ptr;
		} else
			p->s.ptr = bp;
	gfreep = p;
}
