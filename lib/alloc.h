//void* gmemcpy(void*, const void*, size_t);
#include <sys/mman.h>

#include <sys/syscall.h>

#define NALLOC 	10024 
/*
void* gsbrk(intptr_t increment)
{
	void *new, *old = (void *)syscall(__NR_brk, 0);

	new = (void *)syscall(__NR_brk, ((uintptr_t)old) + increment);
	
	return (((uintptr_t)new) == (((uintptr_t)old) + increment)) ? old :
	(void *)-1;
}
*/

typedef long Align;

union header {			
	struct {
		union header	*ptr;  
		unsigned 	size;	
	} s;
	Align x;			
};

typedef union header Header;

static Header base;		
static Header *gfreep = NULL;	

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

Header *morecore(unsigned nu)
{
	char *cp, *isbrk(intptr_t);
	void gfree(void*);
	Header *up;
	if (nu < NALLOC)
		nu = NALLOC;
	/* Old K&R sbrk() changed out to a more modern mmap() technique */
	/* cp = sbrk(nu * sizeof(Header)); */
	cp = mmap( 0, nu* sizeof(Header), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
	if (cp == (char *) -1)	
		return NULL;
	up = (Header*) cp;
	up->s.size = nu;	
	gfree((void*)(up+1));	
	return gfreep;
}

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

