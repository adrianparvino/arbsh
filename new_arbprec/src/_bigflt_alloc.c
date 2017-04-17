#include <arbprec/arbprec.h>

bigflt *_bigflt_alloc(size_t len)
{
	bigflt *ret = malloc(sizeof (bigflt));
	ret->number = malloc(sizeof(int) * len);
	ret->sign = '+';
	ret->float_pos = 0;
	ret->len = len;
	return ret;
}

