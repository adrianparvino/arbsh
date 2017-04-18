#include <arbprec/arbprec.h>


void arbprec_print(bigflt *flt)
{
	
	/*
		Convert a bigflt to a string and print it to standard out
		in a single `write'.

		TODO:
			It may be easier to use sprintf/printf to accumulate
			the buffer to simplify debugging bigflt's

	*/

        size_t i = 0;
	size_t j = 0;
	size_t chunk = BUFSIZ / 16;
	size_t allocated = chunk;
	char *buf = arbprec_malloc(sizeof(char) * allocated);

	if ( flt->sign )
		buf[j++] = flt->sign;

        for ( i = 0; i < flt->len ; ++i)
	{
		if ( flt->float_pos == i )
			buf[j++] = '.';
		if ( j == allocated )
		{
			allocated += chunk;
			buf = arbprec_realloc(buf, sizeof(char) * allocated);
		}
		buf[j++] = (flt->number[i] + '0');
	}
	
	if ( j == allocated )
	{
		allocated += chunk;
		buf = arbprec_realloc(buf, sizeof(char) * allocated);
	}
	buf[j++] = '\n';
	buf[j++] = '\0';
	write(1, buf, j);
	free(buf);
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
	bigflt *ret = arbprec_malloc(sizeof(bigflt));

	ret->sign = '+';
	ret->len = 0;
	ret->allocated = chunk;
	ret->number = arbprec_malloc(sizeof(int) * ret->allocated);

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
			if ( ret->len == ret->allocated)
			{
				ret->allocated += chunk;
				ret->number = arbprec_realloc(ret->number, sizeof(int) * ret->allocated);
			}
			ret->number[ret->len++] = str[i] - '0';
		}
	}
	if ( flt_set == 0 ) /* not a float so put the "." at the representative end */
		ret->float_pos = ret->len + 1;
	return ret;
}

bigflt *arba_alloc(size_t len)
{
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret->number = arbprec_malloc(sizeof(int) * len);
	ret->sign = '+';
	ret->float_pos = 0;
	ret->len = len;
	ret->allocated = len;
	return ret;
}

void arba_free(bigflt *flt)
{
	if (flt->number)
		free(flt->number);
	free(flt);
}
