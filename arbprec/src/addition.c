#include <arbprec/arbprec.h>

bigflt *arbprec_add_inter(bigflt *a, bigflt *b, bigflt *c)
{ 
	size_t width = 0; 
	size_t diff = 0;
	size_t i = 0;
	size_t al = a->len;
	size_t bl = b->len;
	int sum = 0;
	int carry = 0;


	arbprec_match_precision(a, b);
	if (b->float_pos > 0 && b->number[0] == 0)
        {
                b->number = b->number + 1;
                b->len -= 1;
                b->float_pos -= 1;

        }
        if (a->float_pos > 0 && a->number[0] == 0)
        {
                a->number = a->number + 1;
                a->len -= 1;
                a->float_pos -= 1;

        }
	al = a->len;
	bl = b->len;
	
	c->float_pos = MAX(rl(a), rl(b));
	c->len = 0;
	
	/*
	if( rr(a) > rr(b))
	{ 
		diff = arbprec_balance_sum(a, b, c, diff);
		al = a->len - diff;
	}
	else if ( rr(b) > rr(a))
	{
		diff = arbprec_balance_sum(b, a, c, diff);
		bl = b->len - diff;
	} 
	*/

	width = MAX(al, bl);
	
        for( ; c->len < width + diff ; c->len++, i++)
	{ 
		sum = hasplace(a->number, i, al) + hasplace(b->number, i, bl) + carry;
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
                c->number[c->len] = sum;
        }
        if (carry)
	{
		c->number[c->len++] = 1;
		c->float_pos += 1;
		//c->len--;
	}

	arbprec_reverse(c->number, c->len);
	return c;
}

bigflt *arbprec_add(bigflt *a, bigflt *b, bigflt *c)
{
	arbprec_initsign(c);

	if (arbprec_isnegati(a) && arbprec_isnegati(b))
		arbprec_setsign(c);
	else if (arbprec_isnegati(a))
		return c = arbprec_sub_inter(b, a, c);
	else if (arbprec_isnegati(b))
		return c = arbprec_sub_inter(a, b, c);

	return c = arbprec_add_inter(a, b, c);
}


