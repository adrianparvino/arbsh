#include "arb_str.h"

int base = 10;

char *arb_str_divide(signed char *a, signed char *b, signed char *c)
{
	size_t i = 0;
	size_t j = 0;
	size_t z = 0;
	size_t numer = gstrlen(a);
	size_t denom = gstrlen(b);
	int sum = 0; 				/* hold a temporary signed value <= base */
	int rec = 0; 				/* boolean record */
	size_t len = 0;


	setsign(c);
	if (*a == '-' && ++a)
		setsign(c);
	else if (*a == '+')
	{
		++a;
		numer = gstrlen(a);
	}
	if (*b == '-' && ++b)
		setsign(c);
	else if (*b == '+')
	{
		++b;
		denom = gstrlen(b);
	}
	++c; 

	len = numer + denom;
	gmemset(c, '0', len);
	c[numer + denom] = '\0';
	gmemset(mirror, '0', len);
	gstrcpy(mirror, a); 
	gmemset(tmpmir, '0', len);
	gstrcpy(tmpmir, mirror);

	tmpmir[len] = mirror[len] = 0;

	/* numerator / denominator  =  quotient */
	for ( ; z <numer ; )
	{ 
		gstrcpy(tmpmir, mirror); 
		for (rec = 0, i = 0, j = z; i < denom ; j++ ,i++) 
		{ 
			sum = (mirror[j] - '0' ) - (b[i]- '0'); 
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

	return c;
}

