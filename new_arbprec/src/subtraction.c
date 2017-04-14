#include <arbprec/arbprec.h>

int *subtraction(int *a, int *b, int *c)
{ 
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int mir = 0;
	int borrow = 0;
	int carry = -1;
	size_t wa = arraylen(a, 4242); 
	size_t wb = arraylen(b, 4242);

	width = MAX(wa, wb);

        for( i=0; i < width ; i++)
	{
		sum = hasplace(a, i, wa) - hasplace(b, i, wb) + borrow; 
		mir = hasplace(a, i, wa) - hasplace(b, i, wb) + carry;
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
		c[i] = sum;
		mirror[i] = (base-1) - mir;
        }
	
        c[i] = mirror[i] = 4242; 
	if (borrow == -1)
	{
		verbosity(mirror, "subtraction_r() result was negative", 0, width);
		c = mirror;
	}

	reversestr(c);
	return c;
}
 

