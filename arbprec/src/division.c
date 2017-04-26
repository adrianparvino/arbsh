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

	size_t diff = 0;
	if ( a->float_pos < b->float_pos)
	{
		diff = ( b->float_pos - a->float_pos) - 1;
		setarray(c->number, 0, diff);
		c->len = diff;
		z = diff;
		c->float_pos = 0;
		c->number[z] = 0;
	}else{

		if ( a->float_pos + 1 > b->float_pos)
			c->float_pos = a->float_pos - b->float_pos + 1;
		else
			c->float_pos = a->float_pos;
	}

	int carry = 0;
	for ( ; z < a->len + diff; )
	{
		for (rec = 0, i = 0, j = z - diff; i < b->len ; j++ ,i++)
		{
			sum = (mir[j]) - (b->number[i]);
			if ( sum < 0 )
			{
				if ( j == z - diff)
				{ 
					mir[j + 1] += ((mir[j]) * base);
					z++;
					c->len++;
					//if ( z !=diff )
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
		}
	} 

	free(mir);
	free(tmir);
	return c;
}
