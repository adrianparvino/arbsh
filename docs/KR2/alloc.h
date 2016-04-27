#include <sys/mman.h>

#include <sys/syscall.h>



typedef long Align; /* for alignment to long boundary */
union header {      /* block header */
    struct {
        union header *ptr; /* next block if on kr2free list */
        unsigned size;     /* size of this block */
    } s;
    Align x;           /* force alignment of blocks */
}header;

typedef union header Header;
static Header base;       /* empty list to get started */
static Header *kr2freep = NULL;     /* start of kr2free list */
static Header *kr2freeptr = NULL; 
static Header *prevptr = NULL;
static Header *morecore(unsigned);
void kr2free(void *);
void gfree(void *ap);
static Header *gfreep = NULL;
/* kr2malloc: general-purpose storage allocator */
void *kr2malloc(unsigned nbytes)
{
    Header *p, *prevp;
  Header *moreroce(unsigned);
  unsigned nunits;
  //nunits = (nbytes+sizeof(Header)-1)/sizeof(header) + 1;
  nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
  if ((prevp = kr2freep) == NULL) {   /* no kr2free list yet */
      base.s.ptr = kr2freeptr = prevptr = &base;
      base.s.size = 0;
  }
  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
      if (p->s.size >= nunits) { /* big enough */
          if (p->s.size == nunits) /* exactly */
              prevp->s.ptr = p->s.ptr;
          else {              /* allocate tail end */
              p->s.size -= nunits;
              p += p->s.size;
              p->s.size = nunits;
          }
          kr2freep = prevp;
          return (void *)(p+1);
      }
      if (p == kr2freep) /* wrapped around kr2free list */
          if ((p = morecore(nunits)) == NULL)
              return NULL;    /* none left */
  }
}

#define NALLOC  1024   /* minimum #units to request */
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
/* morecore: ask system for more memory */
//static Header *morecore(unsigned nu)
//{
//    char *cp, *sbrk(int);
//char *cp;
//char *cp, *isbrk(intptr_t);
	
//    Header *up;
//  if (nu < NALLOC)
//      nu = NALLOC;
//  cp = sbrk(nu * sizeof(Header));
//  if (cp == (char *) -1)   /* no space at all */
//      return NULL;
//  up = (Header *) cp;
//  up->s.size = nu;
  //kr2free((void *)(up+1));
//  gfree((void *)(up+1));

//  return kr2freep;
//}
/* kr2free: put block ap in kr2free list */
//void kr2free(void *ap)
//{
//    Header *bp, *p;
    
//    bp = (Header *)ap - 1;    /* point to block header */
//    for (p = kr2freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
//         if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
//             break; /* kr2freed block at start or end of arena */
//    if (bp + bp->size == p->s.ptr) {    /* join to upper nbr */
//        bp->s.size += p->s.ptr->s.size;
//        bp->s.ptr = p->s.ptr->s.ptr;
//    } else
//        bp->s.ptr = p->s.ptr;
//    if (p + p->size == bp) {            /* join to lower nbr */
//        p->s.size += bp->s.size;
//        p->s.ptr = bp->s.ptr;
//    } else
//        p->s.ptr = bp;
//    kr2freep = p;
//}
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

