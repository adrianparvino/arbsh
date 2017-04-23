#include <arbprec/arbprec.h>

bigflt *arbprec_initsign(bigflt *flt)
{
	flt->sign = '+';
	return flt;
}

bigflt *arbprec_setsign(bigflt *flt)
{
	if ( flt->sign == '+' )
		flt->sign = '-';
	else if ( flt->sign == '-' )
		flt->sign = '+';
	return flt;
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


bigflt *arbprec_print_simple(bigflt *flt)
{ 
        size_t i = 0; 

        for (i = 0; i < flt->len ; ++i)
	{ 
		if ( flt->float_pos == i ) 
			printf("."); 
		printf("%d", flt->number[i]); 
	} 
	return flt;
}

bigflt *arbprec_print(bigflt *flt)
{
	
	/*
		Convert a bigflt to a string and print it to standard out
		in a single `write'.

		TODO:
			It may be easier to use sprintf/printf to accumulate
			the buffer to simplify debugging bigflts

	*/

        size_t i = 0;
	size_t j = 0;
	size_t chunk = BUFSIZ / 16;
	size_t allocated = chunk;
	char *buf = arbprec_malloc(sizeof(char) * allocated);

	if ( flt->sign )
		buf[j++] = flt->sign;

        for (i = 0; i < flt->len ; ++i)
	{
		if ( j == allocated )
		{
			allocated += chunk;
			buf = arbprec_realloc(buf, sizeof(char) * allocated);
		}
		
		if ( flt->float_pos == i )
			buf[j++] = '.';
	
		buf[j++] = (flt->number[i] + '0');
	}
	
	if ( j == allocated )
	{
		allocated += chunk;
		buf = arbprec_realloc(buf, sizeof(char) * allocated);
	}
	buf[j++] = '\n';
	buf[j++] = '\0';
	write(1, buf, j -1);
	free(buf);
	return flt;
}

bigflt *str_to_bigflt(const char *str)
{
	/*
		Convert a string to a bigflt and attempt a series of chunk 
		based `realloc's to hold the generated values.

		Try to keep the chunk size aligned with future devices
		by aligning with a size macro such as (SIZE_MACRO / 16).
	*/

	size_t i = 0;
	size_t chunk = BUFSIZ / 16;
	int flt_set = 0;
	int sign_set = 0;
	int padded = 0; 

	bigflt *ret = arba_alloc(chunk);
	

	for (i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == '.')
		{
			flt_set = 1;
			ret->float_pos = i - sign_set - padded;
		}
		else if (str[i] == '+')
		{
			sign_set = 1;
			ret->sign = '+';
		}
		else if (str[i] == '-')
		{
			sign_set = 1;
			ret->sign = '-';
		}
		else if (str[i] == ' ')
			++padded;
		else
		{
			ret = arbprec_expand_vector(ret, ret->len); 
			ret->number[ret->len++] = str[i] - '0';
		}
	}
	if ( flt_set == 0 ) /* not a float so put the "." at the representative end */
		ret->float_pos = ret->len + 1;

	ret->mirror = arbprec_malloc(sizeof(int) * ret->allocated);

	return ret;
}

bigflt *arba_alloc(size_t len)
{
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret->number = arbprec_malloc(sizeof(int) * len);
	ret->mirror = arbprec_malloc(sizeof(int) * len);
	ret->sign = '+';
	ret->float_pos = len + 1;
	ret->len = 0;
	ret->allocated = len;
	ret->chunk = 256;
	return ret;
}

void arba_free(bigflt *flt)
{
	if (flt->number)
		free(flt->number);
	free(flt);
}

bigflt *arbprec_expand_vector(bigflt *flt, size_t request)
{
	size_t chunks = 0;
	if ( request >= flt->allocated )
	{
		chunks = (request / flt->chunk) + 2;
		flt->allocated = flt->chunk * chunks;
		/* rapidly expand size */
		//flt->chunk += flt->chunk;
		flt->number = arbprec_realloc(flt->number, flt->allocated * sizeof(int));
		flt->mirror = arbprec_realloc(flt->mirror, flt->allocated * sizeof(int));
	} 
	return flt;
}

