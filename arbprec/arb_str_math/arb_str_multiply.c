#include <arb_str/arb_str.h> 

char *arb_str_multiply(char *a, char *b, char *c)
{
	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;
	int la = 0;
	int lb = 0;

	/* see if either a or b is negative */
	setsign(c);
	if (*a == '-' && ++a)
		setsign(c);
	else if (*a == '+')
		++a;
	if (*b == '-' && ++b)
		setsign(c);
	else if (*b == '+')
		++b;
	++c;
	
	/* either is zero, return c "0" */
	if (!strcmp(a, "0") || !strcmp(b, "0"))
	{ 
		c[0] = '0';
		c[1] = '\0';
		return c - 1;
	}
 
	la = strlen(a);
	lb = strlen(b);
	
	memset(c, '0', la + lb);
	c[la + lb] = '\0'; 

	for ( i = la - 1; i >= 0 ; i--)
	{
		for ( j = lb - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--) 
		{
			sum = (a[i]-'0') * (b[j]-'0') + (c[k]-'0') + carry;
			carry = sum / 10;
			c[k] = (sum % 10) + '0'; 
		}
		c[k] += carry; 
	}

	--c;
	return c;
}
