#include <arbprec.h>

void arb_short_mul(unsigned char *a, size_t i, int b, int base)
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

void short_mul2(unsigned char *a, unsigned char *c, size_t i, int b, int base)
{
	/* c = a * b */
	int carry;
	int value;
	if (b == 0)
		memset (c, 0, i);
	else if (b == 1)
		memcpy (c, a, i);
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

void short_multiply(unsigned char *num, int size, int digit, unsigned char *result, int base)
{
	int carry, value;
	size_t i = 0;

	if (digit == 0)
		memset (result, 0, size);
	else if (digit == 1)
		memcpy (result, num, size);
	else
	{
		for (carry = 0, i = size ; i>0;i--)
		{
			value = num[i-1] * digit + carry;
			result[i-1] = value % base;
			carry = value / base;

		}
		if (carry != 0)
			result[i-1] = carry;
	}
}

