#include <arbprec/arbprec.h>

bigflt *str_to_bigflt(const char *str)
{
	size_t i = 0;
	size_t chunk = 512;
	bigflt *ret = arbprec_malloc(sizeof(bigflt));

	ret->len = 0;
	ret->allocated = chunk;
	ret->number = arbprec_malloc(sizeof(int) * ret->allocated);

	for (i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == '.')
			ret->float_pos = i;
		else if (str[i] == '+')
			ret->sign = '+';
		else if (str[i] == '-')
			ret->sign = '-';
		else {
			if ( ret->len == ret->allocated)
			{
				ret->allocated += chunk;
				ret->number = arbprec_realloc(ret->number, ret->allocated);
			}
			ret->number[ret->len++] = str[i] - '0';
		}
		
	}
	return ret;
}

bigflt *arba_alloc(size_t len)
{
	bigflt *ret = arbprec_malloc(sizeof(bigflt));
	ret->number = arbprec_malloc(sizeof(int) * len);
	ret->sign = '+';
	ret->float_pos = 0;
	ret->len = len;
	return ret;
}

void arba_free(bigflt *fp)
{
	free(fp->number);
	free(fp);
}
