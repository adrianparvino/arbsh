#include <arbprec/arbprec.h>

int *divide(int *a, int *b, int *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0; 
	size_t numer = arraylen(a, 4242);
	size_t denom = arraylen(b, 4242);
	int sum = 0;
	int rec = 0; 

	/* TODO: capture the falling places and increment the *int */
	setarray(c, 0);
	setarray(mirror, 0);
	copyarray(mirror, a);
	setarray(tmpmir, 0);
	copyarray(tmpmir, mirror);

	/* numerator / denominator  =  quotient */
	for ( ; z < numer ; )
	{
		copyarray(tmpmir, mirror);
		for (rec = 0, i = 0, j = z; i < denom ; j++ ,i++) 
		{
			sum = (mirror[j]) - (b[i]);
			if ( sum < 0 )
			{
				if ( j == z )
				{
					mirror[j + 1] += ((mirror[j]) * base);
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
			tmpmir[j] = sum;
		} 
		if ( rec == 0 )
		{ 
			copyarray(mirror, tmpmir); 
			c[z] += 1;
		} 
		if ( iszero(tmpmir) == 0)
			break;
	}
	return c;
}

