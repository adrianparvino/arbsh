#include <arbprec/arbprec.h>

bigflt *arbprec_mul(bigflt *a, bigflt *b, bigflt *c)
{
	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;

	/* see if either a or b is negative */
	arbprec_init(c);
        if (arbprec_isnegati(a))
                arbprec_setsign(c);
        if (arbprec_isnegati(b))
                arbprec_setsign(c);

	c = arbprec_expand_vector(c, a->len + b->len);
	setarray(c->number, 0, a->len + b->len);
	
	for ( i = a->len - 1; i >= 0 ; i--)
	{
		for ( j = b->len - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--)
		{
			sum = (a->number[i]) * (b->number[j]) + (c->number[k]) + carry;
			carry = sum / base;
			c->number[k] = (sum % base);
		}
		c->number[k] += carry;
	}
	c->len = a->len + b->len;
	c->float_pos = rl(a) + rl(b);
	//c->len = ((a->len + b->len) / 2);
	c = strip_zeros(c);
	return c;
}

