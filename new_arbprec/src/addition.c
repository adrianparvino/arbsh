#include <arbprec/arbprec.h> 

/* Functions */ 

bigflt *arbprec_add(bigflt *a, bigflt *b, bigflt *c)
{
	size_t width = 0;
	int sum = 0;
	int carry = 0;
	c->len = 0;

	width = MAX(a->len, b->len);
	
        for( c->len = 0; c->len < width ; c->len++)
	{
		sum = hasplace(a->number, c->len, a->len) + hasplace(b->number, c->len, b->len) + carry;
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
		/* add a vector resize here */
                c->number[c->len] = sum;
        }
        if (carry)
		c->number[c->len++] = 1;
       
	arbprec_reverse(c->number, c->len);
	return c;
}

