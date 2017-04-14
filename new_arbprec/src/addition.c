#include <arbprec/arbprec.h> 

/* Functions */ 
int *addition(int *a, int *b, int *c)
{
	/* 
		TODO: get rid of addition() itself and implement it in terms of subtraction() 
			--> This may require both immutable and mutable signs
	*/
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int carry = 0;
	size_t wa = arraylen(a, 4242);
	size_t wb = arraylen(b, 4242);

	width = MAX(wa, wb);
	
        for( i = 0; i < width ; i++)
	{
		sum = getcharval(a, i, wa) + getcharval(b, i, wb) + carry;
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
                c[i] = sum;
        }
        if (carry)
		c[i++] = 1;
        c[i] = 4242;
       
	reversestr(c);
	return c;
}

