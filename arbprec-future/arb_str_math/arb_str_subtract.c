#include "arb_str.h" 
char *arb_str_subtraction(char *a, char *b, char *c)
{ 
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int mir = 0;
	int borrow = 0;
	int carry = -1;
	size_t wa = gstrlen(a); 
	size_t wb = gstrlen(b);

	if ( wa > wb ) width = wa;
	else width = wb;
	
	setsign(c++);
	*mirror = '\0';
	setsign(mirror++);

        for( i=0; i < width ; i++)
	{
		sum = arb_str_index(a, i) - arb_str_index(b, i) + borrow; 
		mir = arb_str_index(a, i) - arb_str_index(b, i) + carry;
                carry = borrow = 0;
		if(sum < 0)
		{
                        borrow = -1;
                        sum += 10; 
                }
		if(mir < 0)
		{
                        carry = -1;
                        mir += 10; 
                } 
		c[i] = sum + 48;
		mirror[i] = '9' - mir;
        }
	
        c[i] = mirror[i] = '\0'; 
	if (borrow == -1) /// then use the symmetrical mirror 
	{
		c = mirror; 
		if (!(*(a-1) == '-' && *(b-1) == '-'))
			setsign(c - 1); 
	}
        arb_str_rev(c--);
	return c;
} 

char * arb_str_subtract(char *x, char *y, char *c)
{ 
	if (x[0] == '+')
		++x; 
	if (y[0] == '+')
		++y;
	if (x[0] == '-' && y[0] == '-')
	{
		setsign(c);
		*mirror = '\0';
		setsign(mirror); 
		return c = arb_str_subtraction(x + 1, y + 1, c);
	} 
	else if (x[0] == '-')
	{ 
		setsign(c);
		*mirror = '\0';
		setsign(mirror);
		return c = arb_str_addition(x + 1, y, c);
	}
	else if (y[0] == '-')
	{ 
		return c = arb_str_addition(x, y + 1, c); 
	} else { 
		c = arb_str_subtraction(x, y, c); 
	} 
	return c;
} 
