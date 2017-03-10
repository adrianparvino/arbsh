#include "arb_str.h"

char *arb_str_addition(char *a, char *b, char *c)
{
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int carry = 0;
	size_t wa = gstrlen(a); 
	size_t wb = gstrlen(b); 

	if ( wa > wb ) width = wa;
	else width = wb;

	setsign(c++); 

        for( i=0; i < width ; i++)
	{
		sum = arb_str_index(a, i) + arb_str_index(b, i) + carry;
                carry = 0;
                if(sum > 9){
                        carry = 1;
                        sum -= 10;
                }
                c[i] = sum + 48;
        }
        if (carry)
		c[i++] = '1';
        c[i] = '\0';
        arb_str_rev(c--);
	return c;
} 


char * arb_str_add(char *x, char *y, char *c)
{ 
	if (x[0] == '+')
		++x; 
	if (y[0] == '+')
		++y;

	if ( x[0] == '-' && y[0] == '-' )
	{
		setsign(c);
		return c = arb_str_addition(x + 1, y + 1, c); 
	}
	else if (x[0] == '-')
	{
		setsign(c);
		setsign(c); 
		return c = arb_str_subtraction(y, x + 1, c);
	}
	else if (y[0] == '-')
	{
		return c = arb_str_subtraction(x, y + 1, c);
	} else c = arb_str_addition(x, y, c);
	
	return c; 
}
