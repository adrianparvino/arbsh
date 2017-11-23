#include <arbprec/arbprec.h>

void arb_free(fxdpnt *flt)
{
        if (flt->number)
                free(flt->number);
        free(flt);
}

size_t rr(fxdpnt *flt)
{
        /* Right hand radix position */
        return flt->len - flt->lp;
}

size_t rl(fxdpnt *flt)
{
        /* Left hand radix position */
        return flt->lp;
}

void arb_init(fxdpnt *flt)
{
        flt->sign = '+';
        flt->len = flt->lp = 0;
}

void arb_flipsign(fxdpnt *flt)
{
        if (flt->sign == '+')
                flt->sign = '-';
        else if (flt->sign == '-')
                flt->sign = '+';
}

void arb_setsign(fxdpnt *a, fxdpnt *b, fxdpnt *c)
{
        arb_init(c);
        if (a->sign == '-')
                arb_flipsign(c);
        if (b->sign == '-')
                arb_flipsign(c);
}

void verbose(char *msg)
{
	if (verbosity)
		fprintf(stderr, "%s\n", msg);
}

void arb_error(char *message)
{
        fprintf(stderr, "%s\n", message);
        exit(1);
}

void *arb_malloc(size_t len)
{
        void *ret;
        if(!(ret = malloc(len)))
                arb_error("malloc failed\n");
        return ret;
}
fxdpnt *arb_alloc(size_t len)
{
        // Allocate the basic requirements of a arb `fxdpnt'
        fxdpnt *ret = arb_malloc(sizeof(fxdpnt));
        ret->number = arb_malloc(sizeof(ARBT) * len);
        ret->sign = '+';
        ret->lp = 0;
        ret->allocated = len;
        ret->len = 0;
        ret->chunk = 4; // set to 4 to force worst case tests, change to >255
        return ret;
}

void *arb_realloc(void *ptr, size_t len)
{
        void *ret;
        if(!(ret = realloc(ptr, len)))
                arb_error("realloc failed\n"); // FIXME: return an error, and inform the user
					       // of exhausted memory. exit() is not a solution
        return ret;
}

fxdpnt *arb_expand(fxdpnt *flt, size_t request)
{
        // Enlarge or create a fxdpnt
        if (flt == NULL){
	//	arb_init(flt);
                flt = arb_alloc(request); // do not use sizeof here, it's in arb_alloc
		flt->allocated = request;
        } else if (request > flt->allocated){
                flt->allocated = (request + flt->chunk);
                flt->number = arb_realloc(flt->number, flt->allocated * sizeof(ARBT));
        }
        return flt;
}

fxdpnt *arb_create(int length, int scale)
{
	fxdpnt *ret;
	ret = arb_malloc(sizeof(fxdpnt));
	ret->sign = '+';
	ret->lp = length;
	ret->rp = scale;
	ret->allocated = length+scale;
	ret->len = ret->lp + ret->rp;
	ret->number = arb_malloc((length+scale) * sizeof(ARBT));
	ret->chunk = 4;
	memset(ret->number, 0, (length+scale) * sizeof(ARBT));
	return ret;
}

void arb_free_num (fxdpnt *num)
{
	if (num == NULL)
		return;
	if ((num)->number)
		free ((num)->number);
	free (num);
	num = NULL;
}

