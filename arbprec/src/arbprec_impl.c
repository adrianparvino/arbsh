#include <arbprec/arbprec.h>

/* Functions */ 
void arbprec_die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
} 

int arbprec_isnegati(bigflt *flt)
{
        if ( flt->sign == '-' )
                return 1;
        return 0;
}

void arbprec_reverse(int *x, size_t lim)
{
        size_t i = 0;
        int swap = 0;
        size_t half = lim / 2;

        for ( ; i < half ; i++)
        {
                swap = x[i];
                x[i] = x[lim - i - 1];
                x[lim - i - 1] = swap;
        }
}

void *arbprec_malloc(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		arbprec_die("malloc failed\n"); 
	return ret;
}

void *arbprec_realloc(void *ptr, size_t len)
{
	void *ret;
	if(!(ret = realloc(ptr, len)))
		arbprec_die("realloc failed\n"); 
	return ret;
}

void copyarray(int *answer, int *from, size_t len)
{ 
	size_t i = 0;
	for( i = 0; i < len ; i++)
		answer[i] = from[i];
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

void setarray(int *answer, int delim, size_t len)
{
	size_t i = 0;
	for( i = 0; i < len; i++)
		answer[i] = delim;
}
