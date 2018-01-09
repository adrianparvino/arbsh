#include <arbprec/arbprec.h>

fxdpnt *hrdware2arb(size_t a)
{
	/* TODO: this is not very efficient, replace it with itoa style code */
	char str[50]; /* there is no hardware type this long */
	sprintf(str, "%zu", a);
	fxdpnt *ret = arb_str2fxdpnt(str);
	return ret;
}

