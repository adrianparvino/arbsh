#include <arbprec/arbprec.h>

bigflt *arbprec_sub_inter(bigflt *a, bigflt *b, bigflt *c)
{
        size_t width = 0;
        int sum = 0;
        int mir = 0;
        int borrow = 0;
        int carry = -1;
	c->len = 0;

        width = MAX(a->len, b->len);

        for( c->len=0; c->len < width ; c->len++)
        {
                sum = hasplace(a->number, c->len, a->len) - hasplace(b->number, c->len, b->len) + borrow;
                mir = hasplace(a->number, c->len, a->len) - hasplace(b->number, c->len, b->len) + carry;
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
		c->number = c->mirror;
		//if (!( arbprec_isnegati(a) && arbprec_isnegati(b) ))
		arbprec_setsign(c);
	}

        arbprec_reverse(c->number, c->len);
        return c;
}

bigflt *arbprec_sub(bigflt *a, bigflt *b, bigflt *c)
{
        arbprec_initsign(c);

        if ( arbprec_isnegati(a) && arbprec_isnegati(b) )
        {
                arbprec_setsign(c);
                c = arbprec_sub_inter(a, b, c);
        }
        else if ( arbprec_isnegati(a))
        {
                arbprec_setsign(c);
                c = arbprec_add_inter(a, b, c);
        }
        else if ( arbprec_isnegati(b))
        { 
                c = arbprec_add_inter(a, b, c);
        }
        else c = arbprec_sub_inter(a, b, c);

        return c;
}
 
