#include <arbprec.h>

void arb_short_mul(ARBT *a, size_t i, int b, int base)
{
	/* a *= b */
        int carry = 0;
        for (; i > 0 ; i--)
        {
                a[i-1] *= b;
                a[i-1] += carry;
                carry = a[i-1] / base;
                a[i-1] %= base;
        }
}

void short_mul2(ARBT *a, ARBT *c, size_t i, int b, int base)
{
	/* c = a * b */
	long int carry;
	long int value;
	if (b == 0)
		memset (c, 0, i * sizeof(ARBT));
	else if (b == 1)
		memcpy (c, a, i * sizeof(ARBT));
	else
	{
		for (carry = 0; i > 0 ; i--)
		{
			value = a[i-1] * b;
			value += carry;
			c[i-1] = value % base;
			carry = value / base;

		}
		if (carry)
			c[i-1] = carry;
	}
}

