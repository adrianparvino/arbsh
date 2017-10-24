#include <arbprec/arbprec.h>

bigflt *arbprec_initsign(bigflt *flt)
{
	/* Initialize the sign to positive */
	flt->sign = '+';
	return flt;
}

bigflt *arbprec_init(bigflt *flt)
{ 
	/* Reset the length and sign of a bigflt so it can be
		reused for a new answer */
	flt = arbprec_initsign(flt);
	flt->nan = flt->inf = flt->len = flt->float_pos = 0;
	return flt;
}

bigflt *arbprec_setsign(bigflt *flt)
{
	/* Flip the sign of a bigflt */
	if ( flt->sign == '+' )
		flt->sign = '-';
	else if ( flt->sign == '-' )
		flt->sign = '+';
	return flt;
}

int arba_idioma(int a)
{
	/* This table provides a method for printing larger bases. I don't know
		of a standard for handling bases this large so it is roughly
		based on base64 encoding, with any values over 64 simply 
		allowed to default to their native character encoding 
	*/
	static int glyphs[65] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
				'9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
				'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
				'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
				'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
				'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '+',
				'/', '='};
	if ( a <= 64 )
		return glyphs[a];
	else
		return a;
}

bigflt *arbprec_print(bigflt *flt)
{ 
	/* Print a bigflt in chunks of BUFSIZ */
	size_t i = 0;

	if ( flt->sign ) 
		putchar(flt->sign);
	
	if (flt->nan == 1)
	{
		puts("nan");
		goto end;
	}
	
	if (flt->inf == 1)
	{
		puts("inf");
		goto end;
	}
	
	//for (i = 0; i < flt->len && i < scale; ++i)
	for (i = 0; i < flt->len ; ++i)
	{
		if (flt->float_pos == i)
			putchar('.');
		putchar(arba_idioma((flt->number[i])));
	}
	end:
	putchar('\n');
	fflush(stdout);
	return flt;
}

bigflt *str_to_bigflt(const char *str)
{
	/* Convert a string to a bigflt */ 
	size_t i = 0;
	int flt_set = 0;
	int sign_set = 0;
	int padded = 0;

	bigflt *ret = arbprec_expand_vector(NULL, 512);

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
	
	if ( flt_set == 0 ) 
		ret->float_pos = ret->len; 

	return ret;
}

bigflt *arba_alloc(size_t len)
{
	/* Allocate the basic requirements of a bigflt */
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret->number = arbprec_malloc(sizeof(int) * len);
	ret->mirror = arbprec_malloc(sizeof(int) * len);
	ret->nr = ret->number;
	ret->mr = ret->mirror;
	ret->sign = '+';
	ret->float_pos = ret->allocated = len;
	ret->len = 0;
	ret->nan = 0;
	ret->inf = 0;
	ret->chunk = 256;
	return ret;
}

void arba_free(bigflt *flt)
{ 
	if (flt->nr)
		free(flt->nr);
	if (flt->mr)
		free(flt->mr);
	free(flt);
}

bigflt *arbprec_expand_vector(bigflt *flt, size_t request)
{
	/* Enlarge or create a bigflt */
	if (flt == NULL)
	{
		flt = arba_alloc(request);
	} else if ( request >= flt->allocated )
	{ 
		/* align chunk requests */
		//chunks = (request / flt->chunk) + 2;
		//flt->allocated += flt->chunk * chunks; 
		flt->allocated = (request + flt->chunk);
		flt->number = flt->nr = arbprec_realloc(flt->nr, flt->allocated * sizeof(int)); 
		flt->mirror = flt->mr = arbprec_realloc(flt->mr, flt->allocated * sizeof(int));
	} 
	return flt;
}


bigflt *arbprec_copy(bigflt *dest, bigflt *src)
{
	/* Copy a bigflt */
	dest = arbprec_expand_vector(dest, src->len);
	copyarray(dest->number, src->number, src->len);
	copyarray(dest->mirror, src->mirror, src->len); 
	dest = arbprec_copy_info(dest, src);
	return dest;
}

bigflt *arbprec_dup_sparse_mirror(bigflt *src)
{
	/* Sparsely duplicate a bigflt and flip its sign */
	bigflt *ret = arbprec_dup_sparse(src);
	arbprec_setsign(ret);
	return ret;
}

bigflt *arbprec_copy_sparse(bigflt *dest, bigflt *src)
{
	/* Make a sparse copy of a bigflt */
	dest = arbprec_copy_info(dest, src);
	dest->number = src->number;
	dest->mirror = src->mirror;
	return dest;
}

bigflt *arbprec_copy_info(bigflt *dest, bigflt *src)
{
	dest->sign = src->sign;
	dest->len = src->len;
	dest->chunk = src->chunk;
	dest->allocated = src->allocated;
	dest->float_pos = src->float_pos; 
	dest->nan = src->nan;
	dest->inf = src->inf;
	return dest;
}

bigflt *arbprec_dupa(bigflt *flt)
{ 
	/* Duplicate a bigflt */
	bigflt *ret = arbprec_expand_vector(NULL, flt->len);
	ret = arbprec_copy(ret, flt);
	return ret;
}

bigflt *arbprec_dup_sparse(bigflt *flt)
{
	/* Sparsely duplicate a bigflt */
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret = arbprec_copy_sparse(ret, flt);
	return ret;
}

size_t rr(bigflt *flt)
{
	/* Right hand radix position */
	return flt->len - flt->float_pos;
}

size_t rl(bigflt *flt)
{
	/* Left hand radix position */
	return flt->float_pos;
}

void rst(bigflt *flt, size_t radix)
{
	/* Set the left hand radix. */
	flt->float_pos = radix;
}

void arbprec_match_precision(bigflt *a, bigflt *b)
{ 
	/* Match the precision of a number with that of another by
		reallocating sufficient memory for it and then appending 0s */
	size_t off = 0;
	if (rr(b) < rr(a))
	{
		off = rr(a) - rr(b);
		b = arbprec_add_precision(b, off); 
	} 
	else if (rr(b) > rr(a))
	{
		off = rr(b) - rr(a);
		a = arbprec_add_precision(a, off); 
	} 
}

bigflt *arbprec_add_precision(bigflt *flt, size_t off)
{
	/* Increase the precision of a number */
	flt = arbprec_expand_vector(flt, flt->len + off);
	setarray(flt->number + flt->len, 0, off);
	flt->len += off;
	return flt;
} 

void arbprec_die(char *message)
{
	fprintf(stderr, "%s\n", message);
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

int place(bigflt *flt, size_t idx)
{
	if (idx < flt->len)
		return flt->number[flt->len - idx - 1];
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

bigflt *strip_zeros(bigflt *b)
{
	while (b->float_pos > 0 && b->len > 0 && b->number[0] == 0)
	{ 
		copyarray(b->number, b->number + 1, b->len);
       		b->len -= 1; 
		b->float_pos -= 1;
	} 
	return b;
}

int arbprec_compare(bigflt *a, bigflt *b)
{
	size_t i = 0;
	/* The number to the left of the radix is simply "longer" */
	if (rl(a) > rl(b))
		return 1;
	if (rl(a) < rl(b))
		return -1;
	/* The numbers are of equal lengths to the left of the radix */
	for (i=0 ;i < a->len && i < b->len; ++i)
	{
		if (a->number[i] != b->number[i]) 
		{
			if (a->number[i] > b->number[i])
				return 1;
			if (a->number[i] < b->number[i])
				return -1;
		}
	}
	/* There may still be a value trailing to the far right of the radix */
	if (rr(a) > rr(b))
		return 1;
	if (rr(a) < rr(b))
		return -1;
	/* The regular case of two equal numbers */
	return 0;
}
