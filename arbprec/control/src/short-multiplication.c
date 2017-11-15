#include <arbprec.h>

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

