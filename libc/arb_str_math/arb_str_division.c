#include "arb_str.h"

int arb_str_base = 10;



char *arb_str_divide(char *a, char *b, char *cc)
{
	size_t i = 0;
	size_t j = 0;
	size_t z = 0;
	size_t numer = gstrlen(a) + 1;
	size_t denom = gstrlen(b) + 1;
	int sum = 0;
	int rec = 1;
	size_t len = 0;
	char *mir;
	char *tmir;
	char *temp;
	setsign(cc);
	if (*a == '-' && ++a) 
	{
		setsign(cc);
		--numer;
	}
	else if (*a == '+')
	{
		++a;
		--numer;
	}
	if (*b == '-' && ++b) 
	{
		setsign(cc); 
		--denom;
	}
	else if (*b == '+')
	{
		++b; 
		--denom;
	}
	++cc;

	len = numer + denom + 2;
	temp = gmalloc(len);
	tmir = gmalloc(len);
	mir = gmalloc(len);
	gstrncpy(mir + 1, a, len);
	gstrncpy(tmir + 1, a, len);
	gstrncpy(temp + 1, b, len);
	mir[0] = temp[0] = '0';
	cc[numer + denom] = 0;
	

	/* numerator / denominator  =  quotient */

	for (cc[0] = '0'; z <numer ; cc[z+1] = '0' )
	{ 
		
		gstrcpy(tmir, mir); 
		for (rec = 0, i = 0, j = z; i < denom ; ++i, ++j) 
		{ 
			sum = (mir[j] - '0' ) - (temp[i]- '0'); 
			if ( sum < 0 )
			{ 
				if ( j == z )
				{ 
					mir[j + 1] += ((mir[j]-'0') * arb_str_base);
					++z;
				}
			 	else
				{ 
					mir[j - 1] -= 1 ;
					mir[j] += arb_str_base;
				}
				rec = 1;
				break; 
			}
			
			tmir[j] = sum + '0'; 
		} 
		
		if ( rec == 0 )
		{ 
			gstrcpy(mir, tmir); 
			cc[z] += 1;
		} 
	} 
	gfree(temp);
	gfree(tmir);
	gfree(mir);
	cc[numer - denom + 1] = 0;
	--cc; 
	return cc;
}

