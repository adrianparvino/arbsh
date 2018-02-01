#include <arbprec/arbprec.h>

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

