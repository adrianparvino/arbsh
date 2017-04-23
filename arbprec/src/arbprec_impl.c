#include <arbprec/arbprec.h>

/* Functions */
void *arbprec_malloc(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		die("malloc failed\n"); 
	return ret;
}

void *arbprec_realloc(void *ptr, size_t len)
{
	void *ret;
	if(!(ret = realloc(ptr, len)))
		die("realloc failed\n"); 
	return ret;
}

void copyarray(int *answer, int *from, size_t len)
{
	size_t i = 0;
	for( i = 0; i < len ; i++)
		answer[i] = from[i];
}

void die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

int hasplace(int *s, size_t idx, size_t len)
{
        if (idx < len)
        	return s[len - idx - 1];
        return 0;
} 

int iszero(int *answer, size_t lim)
{
	size_t i = 0;
	for ( i = 0; i < lim ; i++)
		if ( answer[i] )
			return 1;
	return 0;
}

void setarray2(int *answer, int delim, size_t len)
{
	size_t i = 0;
	for( i = 0; i < len; i++)
		answer[i] = delim;
}

void setarray(int *answer, size_t len)
{
	size_t i = 0;
	for( i = 0; i < len; i++)
		answer[i] = 0;
}
bigflt *arbprec_copy(bigflt *dest, bigflt *src)
{
	dest = arbprec_expand_vector(dest, src->len);
	copyarray(dest->number, src->number, src->len);
	copyarray(dest->mirror, src->mirror, src->len);
	dest->sign = src->sign;
	/* these should already have been set by expand_vector */
	dest->len = src->len;
	dest->chunk = src->chunk;
	dest->allocated = src->allocated;
	dest->float_pos = src->float_pos;

	return dest;
}

bigflt *arbprec_dupa(bigflt *flt)
{
	bigflt *ret = arbprec_expand_vector(NULL, flt->len);
	arbprec_copy(ret, flt);
	return ret;
}

