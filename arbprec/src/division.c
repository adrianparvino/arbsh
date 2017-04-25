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

	arbprec_init(c);

        if (arbprec_isnegati(a))
                arbprec_setsign(c);
        if (arbprec_isnegati(b))
                arbprec_setsign(c);

	setarray(mir + a->len, 0, width - a->len);
	copyarray(mir, a->number, a->len);
	c->number[z] = 0;

	for ( ; z < a->len ; )
	{
		for (rec = 0, i = 0, j = z; i < b->len ; j++ ,i++)
		{
			sum = (mir[j]) - (b->number[i]);
			if ( sum < 0 )
			{
				if ( j == z )
				{
					mir[j + 1] += ((mir[j]) * base);
					++z;
					c->number[z] = 0;
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
			copyarray(mir, tmir, j);
			c->number[z] += 1;
			c->len = z + 1;
		}
	}

	if ( a->len + 1 > b->len )
		c->float_pos = a->len - b->len + 1;
	else
		c->float_pos = a->len;

	free(mir);
	free(tmir);
	return c;
}
