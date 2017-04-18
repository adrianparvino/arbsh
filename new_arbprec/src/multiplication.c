#include <arbprec/arbprec.h>


bigflt *arbprec_mul(bigflt *a, bigflt *b, bigflt *c)
{
	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;

	memset(c->number, 0, 100);

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
	return c;
}

