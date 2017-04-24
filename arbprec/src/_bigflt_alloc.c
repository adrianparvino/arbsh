#include <arbprec/arbprec.h>

bigflt *arbprec_initsign(bigflt *flt)
{
	flt->sign = '+';
	return flt;
}


bigflt *arbprec_init(bigflt *flt)
{
	arbprec_initsign(flt);
	flt->len = 0;
	flt->float_pos = flt->len + 1;
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
	
	char *buf = arbprec_malloc(sizeof(char) * (flt->len + 4)); // 4 == '+','.','\n','\0'
	size_t i = 0;
	size_t j = 0;

	if ( flt->sign )
		buf[j++] = flt->sign;

        for (i = 0; i < flt->len ; ++i)
	{ 
		if ( flt->float_pos == i )
			buf[j++] = '.';
	
		buf[j++] = (flt->number[i] + '0');
	} 
	buf[j++] = '\n';
	buf[j++] = '\0';
	write(1, buf, j - 1);
	free(buf);
	return flt;
}

bigflt *str_to_bigflt(const char *str)
{
	size_t i = 0;
	size_t chunk = BUFSIZ / 16;
	int flt_set = 0;
	int sign_set = 0;
	int padded = 0;

	bigflt *ret = arbprec_expand_vector(NULL, chunk);

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

	/* not a float so put the "." at the representative end */
	if ( flt_set == 0 ) 
		ret->float_pos = ret->len + 1;

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
	
	if (flt == NULL)
	{
		flt = arba_alloc(request);
	} else if ( request >= flt->allocated )
	{
		chunks = (request / flt->chunk) + 2;
		flt->allocated = flt->chunk * chunks;
		flt->chunk += flt->chunk;
		flt->number = arbprec_realloc(flt->number, flt->allocated * sizeof(int));
		flt->mirror = arbprec_realloc(flt->mirror, flt->allocated * sizeof(int));
	} 
	return flt;
}

