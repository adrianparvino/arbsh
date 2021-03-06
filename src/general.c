#include <assert.h>
#include <string.h>
#include <arbprec/arbprec.h>

size_t rr(fxdpnt *a)
{
	return a->len - a->lp;
}

fxdpnt *remove_leading_zeros(fxdpnt *c)
{
	int effect = 0;
	size_t i = 0;
	
	for (i=0;c->number[i] == 0 && (c->lp > 1 || (c->lp > 0 && rr(c)));)
	{ 
		c->lp--;
		++i;
		effect = 1;
	}

	if (effect)
	{
		c = arb_leftshift(c, i, 1);
		c->len -= i;
	}
	return c;
}

void arb_free(fxdpnt *flt)
{
	arb_destruct(flt);
	free(flt);
}

void arb_destruct(fxdpnt *flt)
{
	if (flt->number) {
		free(flt->number);
		flt->number = NULL;
		flt->allocated = 0;
	}
}

void arb_init(fxdpnt *flt)
{
	assert(flt);
	flt->sign = '+';
	flt->len = 0;
}

fxdpnt *arb_construct(fxdpnt *flt, size_t len)
{
	if (!flt) {
		flt = arb_malloc(sizeof(fxdpnt));
	}

	arb_init(flt);
	flt->number = arb_calloc(1, sizeof(ARBT) * len);
	flt->allocated = len;
	flt->len = len;
	flt->lp = 0;
	return flt;
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

void arb_error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void *arb_malloc(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		arb_error("arb_malloc (malloc) failed\n");
	return ret;
}

void *arb_calloc(size_t nmemb, size_t len)
{
	void *ret;
	if(!(ret = calloc(nmemb, len)))
		arb_error("arb_calloc (calloc) failed\n");
	return ret;
}

fxdpnt *arb_alloc(size_t len)
{
	return arb_construct(NULL, len);
}

void *arb_realloc(void *ptr, size_t len)
{
	void *ret;
	if(!(ret = realloc(ptr, len)))
		arb_error("realloc failed\n"); // FIXME: return an error, and inform the user
	return ret;
}

fxdpnt *arb_expand(fxdpnt *flt, size_t request)
{
	/* (re)allocates memory of size sufficient to hold the nearest
	 * power of two elements of type ARBT so that small increments
	 * do not cause us to repeatedly expand our allocation; large
	 * requests are still handled in a single-shot.
	 */

	size_t oreq = request;
	size_t nreq = 2;                   /* 1 = floor, 2 = ceiling  */
	while (oreq >>= 1) { nreq <<= 1; } /* find nearest power of 2 */
	if (flt == NULL) {
		flt = arb_alloc(nreq);
	} else if (nreq > flt->allocated) {
		flt->allocated = nreq;
		flt->number = arb_realloc(flt->number, flt->allocated * sizeof(ARBT));
		memset(flt->number + flt->len, 0, (flt->allocated - flt->len) * sizeof(ARBT));
	}
	return flt;
}
