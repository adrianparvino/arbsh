#include "arb_str.h"

int base = 10;

char *arb_str_divide(char *a, char *b, char *c)
{
	size_t i = 0;
	size_t j = 0;
	size_t z = 0;
	size_t numer = gstrlen(a);
	size_t denom = gstrlen(b);
	size_t real_cardinality = 0;		/* cardinality of the quotient's real part */
	size_t imag_cardinality = 0;		/* cardinality of the quotient's imaginary part */
	int sum = 0; 				/* hold a temporary signed value <= base */
	int rec = 0; 				/* boolean record */

	
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
	
	gmemset(c, '0', numer + denom);
	c[numer + denom] = '\0';
	gmemset(mirror, 0, numer + denom);
	gstrcpy(mirror, a);
	gmemset(tmpmir, 0, numer + denom);
	gstrcpy(tmpmir, mirror);

	/* numerator / denominator  =  quotient */
	for ( ; z < numer ; )
	{
		//copyarray(tmpmir, mirror);
		
		gstrcpy(tmpmir, mirror);
		for (rec = 0, i = 0, j = z; i < denom ; j++ ,i++) 
		{
			sum = (mirror[j]-'0') - (b[i]-'0');
			if ( sum < 0 )
			{
				if ( j == z )
				{
					mirror[j + 1] += ((mirror[j]-'0') * base);
					++z;
				}
			 	else
				{
					mirror[j - 1] -= 1;
					mirror[j] += base;
				}
				rec = 1;
				break; 
			}
			tmpmir[j] = sum + '0';
		} 
		if ( rec == 0 )
		{
			gstrcpy(mirror, tmpmir);
			c[z] += 1;
		} 
	} 
	c[numer - denom + 1] = 0;
	--c;
	return c;
}

