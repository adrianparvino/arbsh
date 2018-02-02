#include <arbprec/arbprec.h>
#include "fxdpnt.h"

int arb_compare(fxdpnt *a, fxdpnt *b, int base)
{
	int result = 0;
	if (a->sign == '-' && b->sign == '+')
		return -1;
	if (a->sign == '+' && b->sign == '-')
		return 1;

	ssize_t idx = MAX(a->lp, b->lp) - 1;
	ssize_t stop = - MAX(rr(a), rr(b));
	for (; idx >= stop && result == 0; idx--) {
		result = arb_digit(a, idx) - arb_digit(b, idx);
	}

	if (a->sign == '-') { // and also b->sign == '-'
		result = 0 - result;
	}

	(void)base;
	return result;
}
