#include <arbprec/arbprec.h>

bigflt *arbprec_add_inter(bigflt *a, bigflt *b, bigflt *c)
{ 
	size_t width = 0;
	size_t i = 0;
	int sum = 0;
	int carry = 0;

	arbprec_match_precision(a, b);
	c->float_pos = MAX(rl(a), rl(b));
	width = MAX(a->len, b->len);
	c = arbprec_expand_vector(c, width);

        for( ; c->len < width ; c->len++, i++)
	{ 
		sum = place(a, i) + place(b, i) + carry;
                carry = 0;
                if(sum >= base)
		{
                        carry = 1;
                        sum -= base;
                }
                c->number[c->len] = sum;
        }
        if (carry)
	{
		c->number[c->len++] = 1;
		c->float_pos += 1;
	}

	arbprec_reverse(c->number, c->len);
	return c;
}

bigflt *arbprec_add(bigflt *a, bigflt *b, bigflt *c)
{
	arbprec_init(c);

	if (arbprec_isnegati(a) && arbprec_isnegati(b))
		arbprec_setsign(c);
	else if (arbprec_isnegati(a))
		return c = arbprec_sub_inter(b, a, c);
	else if (arbprec_isnegati(b))
		return c = arbprec_sub_inter(a, b, c);

	return c = arbprec_add_inter(a, b, c);
}


