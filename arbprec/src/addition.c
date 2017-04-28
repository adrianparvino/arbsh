#include <arbprec/arbprec.h> 

bigflt *arbprec_add_inter(bigflt *a, bigflt *b, bigflt *c)
{

	
	size_t width = 0;
	int sum = 0;
	int carry = 0;

	size_t radix_right_a = (a->len - a->float_pos);
	size_t radix_right_b = (b->len - b->float_pos);
	size_t diff = 0;
	c->len = 0;
	width = MAX(a->len, b->len); 

	if( radix_right_a > radix_right_b ) 
	{
		diff =  radix_right_a - radix_right_b; 
		size_t lim = a->len;
		size_t limi = diff;
		for (; limi> 0; --limi)
			c->number[c->len++] = a->number[a->len-- - 1]; 

		c->float_pos = b->len;
	
	}
	else if ( radix_right_b > radix_right_a )
	{
		diff = radix_right_b  - radix_right_a; 
		size_t lim = b->len;
		size_t limi= diff;
		for (; limi> 0; --limi)
			c->number[c->len++] = b->number[b->len-- - 1]; 
		c->float_pos = a->len;
	}

	

	//

	size_t i = 0;


        for( ; c->len < width ; c->len++, i++)
	{
		sum = hasplace(a->number, i, a->len) + hasplace(b->number, i, b->len) + carry;
		
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
                c->number[c->len] = sum;
        }
        if (carry) 
		c->number[c->len++] = 1;
       	//c->len += 5;
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


