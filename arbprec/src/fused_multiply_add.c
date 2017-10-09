#include <arbprec/arbprec.h>

bigflt *arbprec_fma(bigflt *a, bigflt *b, bigflt *c)
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
	bigflt *y = a;
	bigflt *z = b;

	if ( a->len < b-> len )
	{
		z = a;
		y = b;
	} 
	
	for ( i = y->len -1; i >= 0 ; i--)
	{
		//for ( j = z->len , k = i + j + 1, carry = 0; j >= 0 ; j--, k--)
		//printf("high\n");
		for ( j = z->len -1, k = i + j + 1 ; j >= 0 ; j--, k--)
		{
			//printf("low\n");
			sum = (y->number[i]) * (z->number[j]) + (c->number[k]) + carry;
			//sum = (y->number[i]) + (z->number[j]) + carry;
			
			//carry = sum / base;
			//c->number[k] = (sum % base);
			carry = 0;
			if (sum >= base)
			{
				sum -= base;
				carry =1;
			}
			c->number[k] = sum;
		}
		//c->number[k] += carry;
	}
	c->len = a->len + b->len;
	c->float_pos = rl(a) + rl(b);
	c->len = ((a->len + b->len) / 2);
	c = strip_zeros(c);
	return c;
}

