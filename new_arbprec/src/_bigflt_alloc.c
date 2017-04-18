#include <arbprec/arbprec.h>

void arbprec_print(bigflt *flt)
{
        size_t i = 0;

	if ( flt->sign )
		printf("%c", flt->sign);

        for ( i = 0; i < flt->len ; ++i)
	{
		if ( flt->float_pos == i )
			printf("."); 
		
		printf("%d", flt->number[i]);
	}

        printf("\n");
} 

bigflt *str_to_bigflt(const char *str)
{
	/*
		convert a string to a bigflt and attempt a series of chunk 
		based `realloc's to hold the generated values.

		Try to keep the chunk size alligned with future devices
		by aligning with a size macro SIZE_MACRO / 16
	*/

	size_t i = 0;
	size_t chunk = BUFSIZ / 16;
	int flt_set = 0;
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
			ret->float_pos = i - 1;
		}
		else if (str[i] == '+')
			ret->sign = '+';
		else if (str[i] == '-')
			ret->sign = '-';
		else if (str[i] == ' ')
			;
		else
		{
			if ( ret->len == ret->allocated)
			{
				ret->allocated += chunk;
				ret->number = arbprec_realloc(ret->number, ret->allocated);
			}
			ret->number[ret->len++] = str[i] - '0';
		}
	}
	if ( flt_set == 0 ) /* no float */
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

void arba_free(bigflt *fp)
{
	free(fp->number);
	free(fp);
}
