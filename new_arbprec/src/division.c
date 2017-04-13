#include <arbprec/arbprec.h>

int *divide(int *a, int *b, int *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0; 
	size_t numer = arraylen(a, 4242);
	size_t denom = arraylen(b, 4242); 
	int *mir = strallocate(sizeof(int) * numer + denom);
	int *tmir = strallocate(sizeof(int) * numer + denom);
	int sum = 0;
	int rec = 0;

	/* TODO: capture the falling places and increment the *int */
	setarray(c, 0);
	setarray(mir, 0);
	copyarray(mir, a);
	setarray(tmir, 0);
	copyarray(tmir, mir);

	/* numerator / denominator  =  quotient */
	for ( ; z < numer ; )
	{
		copyarray(tmir, mir);
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
			copyarray(mir, tmir); 
			c[z] += 1;
		} 
		if ( iszero(tmir) == 0)
			break;
	}
	return c;
}

