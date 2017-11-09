#include <arbprec/arbprec.h>

bigflt *arbprec_sub_inter(bigflt *a, bigflt *b, bigflt *c)
{
        size_t width = 0;
        int sum = 0;
        int mir = 0;
        int borrow = 0;
        int carry = -1;
        size_t i = 0;

	c->float_pos = MAX(rl(a), rl(b)); 
	arbprec_match_precision(a, b);
        width = MAX(a->len, b->len);
	c = arbprec_expand_vector(c, width);

	for( ; c->len < width ; c->len++, i++)
        {
                sum = place(a, i) - place(b, i) + borrow;
                mir = place(a, i) - place(b, i) + carry;
                carry = borrow = 0;
                if(sum < 0)
                {
                        borrow = -1;
                        sum += base;
                }
                if(mir < 0)
                {
                        carry = -1;
                        mir += base;
                }
                c->number[c->len] = sum;
                c->mirror[c->len] = (base-1) - mir; 
        } 
        if (borrow == -1)
	{
		copyarray(c->number, c->mirror, c->len);
		arbprec_setsign(c);
	}

        arbprec_reverse(c->number, c->len);
        return c;
}

bigflt *arbprec_sub(bigflt *a, bigflt *b, bigflt *c)
{
        arbprec_init(c);

        if (arbprec_isnegati(a) && arbprec_isnegati(b))
                arbprec_setsign(c);
        else if (arbprec_isnegati(a))
	{
                arbprec_setsign(c);
		return c = arbprec_add_inter(a, b, c);
	}
        else if (arbprec_isnegati(b) || arbprec_isnegati(a))
                return c = arbprec_add_inter(a, b, c);

        return c = arbprec_sub_inter(a, b, c);
}
 
