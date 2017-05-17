#include <arbprec/arbprec.h>

bigflt *arbprec_scoot(bigflt *a, int cap)
{
	size_t width = a->len + 1;
	a = arbprec_expand_vector(a, width);
	size_t i = 0;

	a->number[0] = cap;

	for (i = width; i > 0; i--) 
		a->number[i + 1] = a->number[i];
	a->len += 1;
	return a;
}
void arbprec_short_add(bigflt *a, int b)
{
	int carry = 0;
        size_t i= a->float_pos -1;

        a->number[i] += b; 

	for (; i>0 ; i--)
	{
		a->number[i] += carry;
		carry = 0;
		if (a->number[i] >= base)
		{
			carry = 1;
			a->number[i] -= base;
		}
	}
	if ( carry == 1 ) 
		a = arbprec_scoot(a, 1);
}

void arbprec_short_sub(bigflt *a, int b)
{
	size_t i= a->float_pos - 1;
	a->number[i] -= b;
	for (; i > 0 ; i--)
	{
		if ( a->number[i] < 0 )
		{
			a->number[i] += base;
			a->number[i - 1]--;
		} 
	}
	a = strip_zeros(a);
}

void arbprec_short_mul(bigflt *a, int b)
{
	int i;
	int carry = 0;
	for ( i = a->len - 1; i >= 0 ; i--)
	{
		a->number[i] *= b;
		a->number[i] += carry;
		carry = a->number[i] / base;
		a->number[i] %= base;
	}
}

void arbprec_short_div(bigflt *a, int b)
{
	int carry = 0;
	size_t i = 0;
	for( i = 0; i < a->len; i++)
	{
		a->number[i] += carry * base;
		carry = a->number[i] % b;
		a->number[i] /= b;
	}
}
