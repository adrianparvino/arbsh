#include <arbprec/arbprec.h>

bigflt *arba_alloc(size_t len)
{
	bigflt *ret = malloc(sizeof(bigflt));
	ret->number = malloc(sizeof(int) * len);
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
