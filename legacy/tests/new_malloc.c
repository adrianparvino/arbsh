#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/syscall.h>
#define NALLOC 10000


void gfree(void *);
void *gmalloc(size_t);
void *grealloc(void *, size_t);
void *gcalloc(size_t, size_t);

#define _ALIGNTYPE long

union header {
	struct {
		union header *ptr;
		size_t size;
	} s;
	_ALIGNTYPE x;
};

typedef union header Header;
static Header base;
static Header *gfreep = NULL;
Header *morecore(unsigned);

void *
_prevgfree(Header *bp)
{
        Header *p;

        for (p = gfreep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
                if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
                        break;
        }
        return p;
}

void *
gmalloc(size_t nbytes)
{
	Header *p, *prevp; 
	size_t nunits;
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

Header *
morecore(unsigned nu)
{
	char *cp;
	Header *up;
	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;
	up = (Header*) cp;
	up->s.size = nu;
	gfree((up+1));
	return gfreep;
}

void
gfree(void *ap)
{
	Header *bp, *p;
    
	bp = (Header*) ap - 1;

	p = _prevgfree(bp);
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
	}
	else
		p->s.ptr = bp;
	gfreep = p;
}

void *
grealloc(void *old_ptr, size_t nbytes)
{
	Header *bp;
	void *new_ptr;
	size_t old_nbytes = 0;

	if (old_ptr == NULL)
		return gmalloc(nbytes);

	bp = (Header *) old_ptr - 1;

	old_nbytes = sizeof(Header) * (bp->s.size -1);

	if (old_nbytes == nbytes)
		return old_ptr;

	if ((new_ptr = gmalloc(nbytes)) == NULL)
		return NULL;

	memcpy(new_ptr, old_ptr, (old_nbytes > nbytes) ? nbytes : old_nbytes);

	gfree(old_ptr);
	return new_ptr;
}

void *
gcalloc(size_t nmemb, size_t size)
{ 
	size_t request;
	void *ret;

	if (size && nmemb > (size_t)-1/size)
                return NULL;
		
	request = nmemb * size;
	if ((ret = gmalloc(request)) != NULL)
		memset(ret, 0, request); 
	
	return ret;
}

int find_pattern(char *, size_t, size_t);

int main(int argc, char *argv[])
{
	//char *string = gcalloc (1000, 1000);

	//write(1, string, 1000);

	if (argc > 1)
		find_pattern(argv[1], strlen(argv[1]), 0);
	else
		find_pattern(".", 1, 0);
	return 0;
}

int find_pattern(char *path, size_t tot, size_t last)
{ 
	DIR *dir;
	struct dirent *d; 
	char *spath = NULL;
	size_t dlen = 0; 
	
	if ( ( dir = opendir(path) ) ) 
	{
		d = readdir(dir); 
		while (d) 
		{ 
			dlen = strlen(d->d_name);
			last = (tot + dlen + 2);
			spath = grealloc(spath, last); 
			tot = sprintf(spath, "%s/%s", path, d->d_name);
			if ( strcmp( ".", d->d_name) && 
			   ( strcmp( "..", d->d_name)) )
			{
				printf("%s\n", spath);
			}

			if ( d->d_type == DT_DIR &&
			   ( strcmp( ".", d->d_name)) &&
			   ( strcmp( "..", d->d_name))) 
				find_pattern(spath, tot, last); 
			d = readdir(dir); 
		}
		
	}
	if ( spath)
		gfree(spath);
	closedir(dir);
	return 0;
}

