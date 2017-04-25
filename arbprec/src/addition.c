#include <arbprec/arbprec.h> 

bigflt *arbprec_add_inter(bigflt *a, bigflt *b, bigflt *c)
{
	size_t width = 0;
	int sum = 0;
	int carry = 0;
	c->len = 0;

	/* TODO: 
		The real and fractional parts of each vector should be expanded to have
		the same width.
	*/

	width = MAX(a->len, b->len);

	c->float_pos = a->float_pos;

        for( c->len = 0; c->len < width ; c->len++)
	{
		sum = hasplace(a->number, c->len, a->len) + hasplace(b->number, c->len, b->len) + carry;
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
                c->number[c->len] = sum;
        }
        if (carry) 
		c->number[c->len++] = 1;
       
	arbprec_reverse(c->number, c->len);
	return c;
}

bigflt *arbprec_add(bigflt *a, bigflt *b, bigflt *c)
{
	arbprec_initsign(c);

	if (arbprec_isnegati(a) && arbprec_isnegati(b))
	{
		arbprec_setsign(c);
		c = arbprec_add_inter(a, b, c);
	}
	else if (arbprec_isnegati(a))
	{ 
		c = arbprec_sub_inter(b, a, c);
	}
	else if (arbprec_isnegati(b))
	{
		c = arbprec_sub_inter(a, b, c);
	}
	else c = arbprec_add_inter(a, b, c);

        return c;
}


