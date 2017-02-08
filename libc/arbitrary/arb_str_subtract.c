#include "stringmath.h" 
char *subtraction(char *a, char *b, char *c)
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
		sum = getcharval(a, i) - getcharval(b, i) + borrow; 
		mir = getcharval(a, i) - getcharval(b, i) + carry;
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
        reversestr(c--);
	return c;
} 

char * subtract(char *x, char *y, char *c)
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
		return c = subtraction(x + 1, y + 1, c);
	} 
	else if (x[0] == '-')
	{ 
		setsign(c);
		*mirror = '\0';
		setsign(mirror);
		return c = addition(x + 1, y, c);
	}
	else if (y[0] == '-')
	{ 
		return c = addition(x, y + 1, c); 
	} else { 
		c = subtraction(x, y, c); 
	} 
	return c;
} 
