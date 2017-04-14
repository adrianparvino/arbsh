#include <arbprec/arbprec.h>

int *divide(int *a, int *b, int *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0; 
	size_t numer = arraylen(a, 4242);
	size_t denom = arraylen(b, 4242);
	int *mir = arbprec_malloc(sizeof(int) * numer + denom);
	int *tmir = arbprec_malloc(sizeof(int) * numer + denom);
	int sum = 0;
	int rec = 0;

	/* TODO: capture the falling places and increment the *int */
	setarray(c, 0, numer + denom);
	setarray(mir, 4242, numer + denom);
	copyarray(mir, a, numer + denom);
	setarray(tmir, 4242, numer + denom);
	copyarray(tmir, mir, numer + denom);

	/* numerator / denominator  =  quotient */
	for ( ; z < numer ; )
	{
		copyarray(tmir, mir, numer + denom);
		for (rec = 0, i = 0, j = z; i < denom ; j++ ,i++) 
		{
			sum = (mir[j]) - (b[i]);
			if ( sum < 0 )
			{
				if ( j == z )
				{
					mir[j + 1] += ((mir[j]) * base);
					++z;
				}
			 	else
				{
					mir[j - 1] -= 1;
					mir[j] += base;
				}
				rec = 1;
				break; 
			}
			tmir[j] = sum;
		} 
		if ( rec == 0 )
		{ 
			copyarray(mir, tmir, numer + denom); 
			c[z] += 1;
		} 
		if ( iszero(tmir) == 0)
			break;
	}
	return c;
}

