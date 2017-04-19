#include <arbprec/arbprec.h>


bigflt *arbprec_div(bigflt *a, bigflt *b, bigflt *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0;
	size_t width = a->len + b->len;
	int *mir = arbprec_malloc(sizeof(int) * width);
	int *tmir = arbprec_malloc(sizeof(int) * width);
	int sum = 0;
	int rec = 0;
	c->len = 0;
	
	setarray(c->number, width);
	setarray(mir, width);
	copyarray(mir, a->number, a->len);
	setarray(tmir, width);
	copyarray(tmir, mir, width);

	
	for ( ; z < a->len ; )
	{
		copyarray(tmir, mir, width);
		for (rec = 0, i = 0, j = z; i < b->len ; j++ ,i++)
		{
			sum = (mir[j]) - (b->number[i]);
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
			c->number[z] += 1;
			c->len = z + 1;
			
		} 
		if ( iszero(tmir, width) == 0 )
			break;
	}

	if ( a->len + 1 > b->len )
                c->float_pos = a->len - b->len + 1;
        else
                c->float_pos = a->len;

	
	free(mir);
	free(tmir);
	return c;
}

