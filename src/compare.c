#include <arbprec/arbprec.h>

#if 1 // remove this after fully test of new implementation
int arb_compare(fxdpnt *a, fxdpnt *b, int base)
{
	size_t i = 0;
	int sign = a->sign;
	if (a->sign == '-' && b->sign == '+')
		return -1;
	if (a->sign == '+' && b->sign == '-')
		return 1;
	fxdpnt *c = NULL;
	c = arb_expand(NULL, a->len + b->len); //FIXME initialize at runtime
	c = arb_sub(a, b, c, base);
	if (c->sign != sign){
		arb_free(c);
		return -1;
	}
	for (;i< c->len;++i){
		if (c->number[i] != 0){
			arb_free(c);
			return 1;
		}
	}
	arb_free(c);
	return 0;
}
#else

int arb_compare(fxdpnt *a, fxdpnt *b, int base)
{
	size_t i;
	int result = 0;
	if (a->sign == '-' && b->sign == '+')
		return -1;
	if (a->sign == '+' && b->sign == '-')
		return 1;

	a = remove_leading_zeros(a);
	b = remove_leading_zeros(b);

	a = remove_trailing_zeros(a);
	b = remove_trailing_zeros(b);

	if (a->lp > b->lp) {
		result = 1;
	} else if (a->lp < b->lp) {
		result = -1;
	} else {
		for (i = 0; i < a->len && i < b->len; ++i) {
			if (a->number[i] > b->number[i]) {
				result = 1;
				break;
			} else if (a->number[i] < b->number[i]) {
				result = -1;
				break;
			}
		}

		// a->lp == b->lp, so fractional parts have different length
		if (i == a->len && i < b->len) {
			result = -1;
		}

		if (i == b->len && i < a->len) {
			result = 1;
		}
	}

	if (a->sign == '-') { // and also b->sign == '-'
		result = 0 - result;
	}

	(void)base;
	return result;
}
#endif
