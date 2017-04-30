
#include <arbprec/arbprec.h> 

size_t helper(bigflt *a, bigflt *b, bigflt *c)
{
	size_t radix_right_a = (a->len - a->float_pos);
	size_t radix_right_b = (b->len - b->float_pos);
	size_t diff = radix_right_a - radix_right_b; 
	size_t limi = diff;
	size_t lim = a->len -1;

	for (; limi> 0; limi--, c->len++, lim--) 
		c->number[c->len] = a->number[lim]; 

	c->float_pos = MAX(a->float_pos, b->float_pos);
	return diff;
}

bigflt *arbprec_add_inter(bigflt *a, bigflt *b, bigflt *c)
{ 
	size_t width = 0;
	int sum = 0;
	int carry = 0;

	size_t radix_right_a = (a->len - a->float_pos);
	size_t radix_right_b = (b->len - b->float_pos);
	size_t diff = 0;
	size_t i = 0;
	
	c->len = 0;
	width = MAX(a->len, b->len);

	size_t al = a->len;
	size_t bl = b->len;
	c->float_pos = MAX(a->float_pos, b->float_pos);

	if( radix_right_a > radix_right_b ) 
	{
		diff = helper(a, b, c);
		al = a->len - diff;
	}
	else if ( radix_right_b > radix_right_a ) 
	{
	
		diff = helper(b, a, c);
		bl = b->len - diff;
	} 
	width = MAX(al, bl);
	
        for( ; c->len < width + diff ; c->len++, i++)
	{
		//arbprec_expand_vector(c, c->len + i );
		sum = hasplace(a->number, i, al) + hasplace(b->number, i, bl) + carry;
		
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
                c->number[c->len] = sum;
		//arbprec_print(c);
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
		arbprec_setsign(c);
	else if (arbprec_isnegati(a))
		return c = arbprec_sub_inter(b, a, c);
	else if (arbprec_isnegati(b))
		return c = arbprec_sub_inter(a, b, c);

	return c = arbprec_add_inter(a, b, c);
}


