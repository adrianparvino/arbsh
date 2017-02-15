#include "arb_str.h"

int base = 10;

char *arb_str_divide(char *a, char *b, char *cc)
{
	ssize_t i = 0;
	size_t j = 0;
	size_t z = 0;
	size_t numer = gstrlen(a);
	size_t denom = gstrlen(b);
	int sum = 0;
	int rec = 0;
	size_t len = 0;

	setsign(cc);
	if (*a == '-' && ++a) 
		setsign(cc); 
	else if (*a == '+')
		++a; 
	if (*b == '-' && ++b) 
		setsign(cc); 
	else if (*b == '+')
		++b; 
	++cc;

	len = numer + denom +1;
	gmemset(cc, '0' , len + 1);
	gmemset(mirror, 0, len + 1);
	gmemset(tmpmir, 0, len + 1); 
	gstrcpy(mirror + 1, a); 
	mirror[0] = '0';
	gstrcpy(tmpmir, mirror); 

	char *temp = malloc(len + 10);
	strcpy(temp + 1, b);
	temp[0] = '0'; 
	
	numer = gstrlen(mirror);
	
	denom = gstrlen(temp); 
	cc[numer + denom] = 0;
	/* numerator / denominator  =  quotient */

	for (; z <numer ; )
	{ 
		
		gstrcpy(tmpmir, mirror); 
		for (rec = 0, i = 0, j = z; i < denom ; ++i, ++j) 
		{ 
			sum = (mirror[j] - '0' ) - (temp[i]- '0'); 
			if ( sum < 0 )
			{ 
				if ( j == z )
				{ 
					mirror[j + 1] += ((mirror[j]-'0') * base);
					++z;
				}
			 	else
				{ 
					mirror[j - 1] -= 1 ;
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
			cc[z] += 1;
		} 
	} 
	free(temp);
	cc[numer - denom + 1] = 0;
	--cc; 
	return cc;
}

