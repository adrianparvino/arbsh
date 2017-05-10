#include <arbprec/arbprec.h>


bigflt *arbprec_initsign(bigflt *flt)
{
	/* 	(internal)
		Initialize the sign to positive
	*/
	flt->sign = '+';
	return flt;
}

bigflt *arbprec_init(bigflt *flt)
{ 
	/*
		Reset the length and sign of a bigflt so it can be
		reused for a new answer
	*/
	flt = arbprec_initsign(flt);
	flt->nan = 0;
	flt->len = 0;
	flt->float_pos = flt->len; 
	return flt;
}

bigflt *arbprec_setsign(bigflt *flt)
{
	/*
		Flip the sign of a bigflt
	*/
	if ( flt->sign == '+' )
		flt->sign = '-';
	else if ( flt->sign == '-' )
		flt->sign = '+';
	return flt;
}

bigflt *arbprec_print_simple(bigflt *flt)
{ 
	/*
		Print a bigflt
	*/
        size_t i = 0; 
	
	if ( flt->sign )
		printf("%c", flt->sign);

	if (flt->nan == 1)
	{
		printf("nan\n");
		return flt;
	}

        for (i = 0; i < flt->len ; ++i)
	{ 
		if ( flt->float_pos == i ) 
			printf("."); 
		printf("%d", flt->number[i]); 
	}
	printf("\n");
	return flt;
}

bigflt *arbprec_print(bigflt *flt)
{ 
	/*
		Print a bigflt in a single write
	*/
	
	
	char *buf = arbprec_malloc(sizeof(char) * (flt->len + 4)); // 4 == '+','.','\n','\0'
	size_t i = 0;
	size_t j = 0;
	size_t wrt_ret = 0;


	if ( flt->sign )
		buf[j++] = flt->sign;

	
	if (flt->nan == 1)
	{
		strcpy(buf + j, "nan");
		j+=3;
		goto end;
	}

        for (i = 0; i < flt->len  && i < scale; ++i)
	{ 
		if ( flt->float_pos == i )
			buf[j++] = '.';
	
		buf[j++] = (flt->number[i] + '0');
	} 
	end:
	buf[j++] = '\n';
	buf[j++] = '\0';
	if ((wrt_ret = write(1, buf, j - 1)) < 1)
		write(2, "write() failed\n", 15);
	free(buf);
	return flt;
}

bigflt *str_to_bigflt(const char *str)
{
	/*
		Convert a string to a bigflt

		'+'/'-' are honored

		' ' whitespace is ignored
	*/
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
	{ 
		ret->float_pos = ret->len;
	}
	

	return ret;
}

bigflt *arba_alloc(size_t len)
{
	/*	(internal)
		Allocate the basic requirements
		of a bigflt
	*/
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret->number = arbprec_malloc(sizeof(int) * len);
	ret->mirror = arbprec_malloc(sizeof(int) * len);
	ret->nr = ret->number;
	ret->mr = ret->mirror;
	ret->sign = '+';
	ret->float_pos = ret->allocated = len;
	ret->len = 0;
	ret->nan = 0;
	ret->chunk = 256;
	return ret;
}

void arba_free(bigflt *flt)
{
	/*
		Free a bigflt
	*/
	if (!flt)
	{
		write(2, "bad free\n", 8);
		return;
	}
		
	if (flt->nr)
		free(flt->nr);
	if (flt->mr)
		free(flt->mr);
	free(flt);
}

bigflt *arbprec_expand_vector(bigflt *flt, size_t request)
{
	/*
		Enlarge or create a bigflt
	*/
	size_t chunks = 0;
	
	if (flt == NULL)
	{
		flt = arba_alloc(request);
	} else if ( request >= flt->allocated )
	{ 
		/* align chunk requests */
		chunks = (request / flt->chunk) + 2;
		flt->allocated = flt->chunk * chunks; 
		flt->number = flt->nr = arbprec_realloc(flt->nr, flt->allocated * sizeof(int)); 
		flt->mirror = flt->mr = arbprec_realloc(flt->mr, flt->allocated * sizeof(int));
	} 
	return flt;
}


bigflt *arbprec_copy(bigflt *dest, bigflt *src)
{
	/*
		Copy a bigflt
	*/
	dest = arbprec_expand_vector(dest, src->len);
	copyarray(dest->number, src->number, src->len);
	copyarray(dest->mirror, src->mirror, src->len);
	dest->sign = src->sign;
	dest->len = src->len;
	dest->float_pos = src->float_pos;
	dest->allocated = src->allocated;
	dest->chunk = src->chunk;
	dest->nan = src->nan;
	/* 
		these should be set by expand_vector 
		->len ->chunk ->allocated ->float_pos
	*/
	return dest;
}
bigflt *arbprec_dup_sparse_mirror(bigflt *src)
{
	/*
		Sparsely duplicate a bigflt and flip its sign
	*/
	bigflt *ret = arbprec_dup_sparse(src);
	arbprec_setsign(ret);
	return ret;
}

bigflt *arbprec_copy_sparse(bigflt *dest, bigflt *src)
{
	/*
		Make a sparse copy of a bigflt
	*/
	dest->sign = src->sign;
	dest->number = src->number;
	dest->mirror = src->mirror;
	dest->len = src->len;
	dest->chunk = src->chunk;
	dest->allocated = src->allocated;
	dest->float_pos = src->float_pos; 
	dest->nan = src->nan;
	return dest;
}

bigflt *arbprec_dupa(bigflt *flt)
{ 
	/*
		Duplicate a bigflt
	*/
	//bigflt *ret = arba_alloc(sizeof(bigflt));
	bigflt *ret = arbprec_expand_vector(NULL, flt->len);
	ret = arbprec_copy(ret, flt);
	return ret;
}

bigflt *arbprec_dup_sparse(bigflt *flt)
{
	/*
		Sparsely duplicate a bigflt
	*/
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret = arbprec_copy_sparse(ret, flt);
	return ret;
}

size_t rr(bigflt *flt)
{
	/* 	(internal)
		Right hand radix position 
	*/
	size_t ret = flt->len - flt->float_pos;
	return ret;
}

size_t rl(bigflt *flt)
{
	/*	(internal)
		Left hand radix position
	*/
	return flt->float_pos;
}

void rst(bigflt *flt, size_t radix)
{
	/*	(internal)
		Set the left hand radix.
	*/
	flt->float_pos = radix;
}

size_t arbprec_balance_sum(bigflt *a, bigflt *b, bigflt *c, size_t diff)
{
	/*
		Strip and record the trailing digits to the right of the radix
		which don't have a match for simpler addition
	*/
        size_t lim = a->len -1;

        diff = rr(a) - rr(b);
        for (; c->len < diff ; c->len++, lim--)
                c->number[c->len] = a->number[lim];

        return diff;
}

void arbprec_match_precision(bigflt *a, bigflt *b)
{ 
	size_t off = 0;
	if (rr(b) < rr(a))
        {
                off = rr(a) - rr(b);
                b = arbprec_expand_vector(b, b->len + off);
                setarray(b->number + b->len , 0, off);
                b->len += off;
        }

        else if (rr(b) > rr(a))
        {
                off = rr(b) - rr(a);
                a = arbprec_expand_vector(a, a->len + off);
                setarray(a->number + a->len , 0, off);
                a->len += off;

        } 
}

bigflt *arbprec_add_precision(bigflt *flt, size_t len)
{
	flt = arbprec_expand_vector(flt, flt->len + len);
	setarray(flt->number + flt->len, 0, len);
	flt->len += len;
	return flt;
	
} 

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

int arpbrec_equals(bigflt *a, bigflt *b, size_t precision)
{
	size_t i = 0;

	for (;i < precision && i < a->len && i < b->len; ++i)
	{
		if (!(a->number[i] == b->number[i]))
			return 0;
	}
	return 1;
}

