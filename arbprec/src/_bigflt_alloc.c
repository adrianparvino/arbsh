#include <arbprec/arbprec.h>

bigflt *arbprec_initsign(bigflt *flt)
{
	flt->sign = '+';
	return flt;
}

bigflt *arbprec_init(bigflt *flt)
{
	/*
		These members should be left alone:
			->chunk ->allocated ->mirror ->number
	*/
	flt = arbprec_initsign(flt);
	flt->len = 0;
	flt->float_pos = flt->len;
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
	size_t wrt_ret = 0;

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
	if ((wrt_ret = write(1, buf, j - 1)) < 1)
		write(2, "write() failed\n", 15);
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
	ret->float_pos = len;
	ret->len = 0;
	ret->allocated = len;
	ret->chunk = 256;
	return ret;
}

void arba_free(bigflt *flt)
{
	if (flt->number)
		free(flt->number);
	if (flt->mirror)
		free(flt->mirror);
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
		//chunks = (request / flt->chunk) + 2;
		//flt->allocated = flt->chunk * chunks;
		//flt->chunk += flt->chunk;
		flt->allocated += flt->chunk + request;
		flt->number = arbprec_realloc(flt->number, flt->allocated * sizeof(int));
		//if ( flt->mirror != NULL)
		flt->mirror = arbprec_realloc(flt->mirror, flt->allocated * sizeof(int));
	} 
	return flt;
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

bigflt *arbprec_copy_sparse(bigflt *dest, bigflt *src)
{
	dest->sign = src->sign;
	dest->number = src->number;
	dest->mirror = src->mirror;
	dest->len = src->len;
	dest->chunk = src->chunk;
	dest->allocated = src->allocated;
	dest->float_pos = src->float_pos;
	return dest;
}

bigflt *arbprec_dupa(bigflt *flt)
{ 
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret = arbprec_copy(ret, flt);
	return ret;
}

bigflt *arbprec_dup_sparse(bigflt *flt)
{
	bigflt *ret = arbprec_expand_vector(NULL, flt->len); 
	ret = arbprec_copy_sparse(ret, flt);
	return ret;
}

