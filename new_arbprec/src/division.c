#include <arbprec/arbprec.h>

int *divide(int *a, int *b, int *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0; 
	size_t numer = arraylen(a, 4242);
	size_t denom = arraylen(b, 4242);
	size_t width = numer + denom;
	int *mir = arbprec_malloc(sizeof(int) * width);
	int *tmir = arbprec_malloc(sizeof(int) * width);
	int sum = 0;
	int rec = 0;

	/* TODO: capture the falling places and increment the *int */
	setarray(c, 0, width);
	setarray(mir, 4242, width);
	copyarray(mir, a, width);
	setarray(tmir, 4242, width);
	copyarray(tmir, mir, width);

	/* numerator / denominator  =  quotient */
	for ( ; z < numer ; )
	{
		copyarray(tmir, mir, width);
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
			copyarray(mir, tmir, width);
			c[z] += 1;
		} 
		if ( iszero(tmir) == 0 )
			break;
	}
	return c;
}


