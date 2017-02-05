#include "stringmath.h"

/* globals */
static char *mirror;
static char *tmpmir;
int verbosity = 0; 

void setsign(char *s)
{
	if (s[0] == '+')
		s[0] = '-';
	else if (s[0] == '-')
		s[0] = '+';
	else 
		s[0] = '+';
} 

size_t reversestr(char *x)
{
        size_t i = 0;
        char swap = 0;
        size_t lim = gstrlen(x);
        size_t half = lim / 2;

        for ( ; i < half ; i++)
        {
                swap = x[i];
                x[i] = x[lim - i - 1];
                x[lim - i - 1] = swap;
        }
        return lim;
} 

void print_real(char *s, char *realname)
{
	if ( verbosity == 0 )
		return;
	size_t i = 0;
	gprintf("------------------------\n");
	gprintf("name:      %s\n", realname);
	gprintf("string:    %s\n", s);
	gprintf("real nums: ");
	
	while (s[i] != '\0')
	{
		gprintf("|%d", s[i] - '0');
		++i;
	}
	gprintf("|\n");
	gprintf("------------------------\n");
}

int getcharval(char *s, size_t idx)
{ 
	size_t len = gstrlen(s);
        if (idx < len)
        	return s[len - idx - 1] - 48;
        return 0;
} 

char *addition(char *a, char *b, char *c)
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
		sum = getcharval(a, i) + getcharval(b, i) + carry;
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
        reversestr(c--);
	return c;
} 

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

char *multiply(char *a, char *b, char *c)
{
	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;
	int la = 0;
	int lb = 0;

	/* see if either a or b is negative */
	setsign(c);
	if (*a == '-' && ++a)
		setsign(c);
	else if (*a == '+')
		++a;
	if (*b == '-' && ++b)
		setsign(c);
	else if (*b == '+')
		++b;
	++c;
	
	/* either is zero, return c "0" */
	if (!gstrcmp(a, "0") || !gstrcmp(b, "0"))
	{ 
		c[0] = '0';
		c[1] = '\0';
		return c - 1;
	}
 
	la = gstrlen(a);
	lb = gstrlen(b);
	
	gmemset(c, '0', la + lb);
	c[la + lb] = '\0'; 

	for ( i = la - 1; i >= 0 ; i--)
	{
		for ( j = lb - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--) 
		{
			sum = (a[i]-'0') * (b[j]-'0') + (c[k]-'0') + carry;
			carry = sum / 10;
			c[k] = (sum % 10) + '0'; 
		}
		c[k] += carry; 
	}

	--c;
	return c;
}

/*
	Wrappers to redirect identities and roll off sign bits.
*/ 
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

char * add(char *x, char *y, char *c)
{ 
	if (x[0] == '+')
		++x; 
	if (y[0] == '+')
		++y;

	if ( x[0] == '-' && y[0] == '-' )
	{
		setsign(c);
		return c = addition(x + 1, y + 1, c); 
	}
	else if (x[0] == '-')
	{
		setsign(c);
		setsign(c); 
		return c = subtraction(y, x + 1, c);
	}
	else if (y[0] == '-')
	{
		return c = subtraction(x, y + 1, c);
	} else c = addition(x, y, c);
	
	return c; 
}

/*
	Manage memory and errors.
*/
void *strallocate(size_t len)
{
	void *ret;
	if(!(ret = gmalloc(len)))
		die("malloc failed\n"); 
	return ret;
} 

void die(char *message)
{
	//gfprintf(gstdout, "%s", message);
	gprintf("%s", message);
	//exit(1);
}


char *division(char *a, char *b, char *c)
{ 
	size_t i = 0;		// Increment over the divisor.
	size_t j = 0;		// Increment over the denominator.
	size_t z = 0;		// Increment through the answer.
	int sum = 0;		// Temporary sum of two digits
	int rec = 0;		// Boolean to control whether or not the mirror is recorded.
	size_t denom = gstrlen(a);	// Cardinality of the denominator.
	size_t divis = gstrlen(b);	// Cardinality of the divisor. 

	gmemset(c, '0', divis + denom);		// Set the result places all to an ASCII zero character
	c[divis + denom] = '\0';		// ASCII NUL cap the result.
	gmemset(mirror, '\0', divis + denom);	// The mirror starts its life as a copy of the denominator,
	gstrcpy(mirror, a);			// otherwise the caller's denominator would be destroyed.
	gmemset(tmpmir, '\0', divis + denom);	// But the mirror can't be modified with bad values,
	gstrcpy(tmpmir, mirror);			// so we have a temporary copy of it too.
	
	for ( ; z < denom ; ) // LOOP OVER DENOMINATOR
	{
		gstrcpy(tmpmir, mirror); // RESET TMPMIR
		for (rec = 0, i = 0, j = z; i < divis ; j++ ,i++) // LOOP OVER DIVISORS
		{
			sum = (mirror[j]-'0') - (b[i]-'0');
			if ( sum < 0 ) 	// REVAL
			{			// HARD REVAL  (borrow all)  B R
				if ( j == z )	// then we have a negative first position and need to carry 
				{		//the last value to the next transaction
					mirror[j + 1] += ((mirror[j] - '0') * 10); // FULL DIGIT CARRY (10 TO 90)
					mirror[j] = '0';	// REMOVE ALL
					print_real(tmpmir, "tmpmir inner loop top HARD REVAL");
					++z;		// only HARD REVALS can change place
				}
			 	else 
				{ 	// SOFT REVAL ( borrow 10 )  R
					// we have a negative non-first position and need to SOFT REVAL by borrowing.
					mirror[j - 1] -= 1;	// REMOVE ONE
					mirror[j] += 10;	// SINGLE TENS BORROW (ALWAYS TEN)
					print_real(tmpmir, "tmpmir inner loop top SOFT REVAL");
				}
				rec = 1; // NO RECORD
				break;
			}
			tmpmir[j] = sum + '0';
			print_real(tmpmir, "tmpmir inner loop bottom GOOD");
		}
		if ( rec == 0 )
		{
			print_real(tmpmir, "tmpmir COPY CANDIDATE  RECORDED");
			gstrcpy(mirror, tmpmir);  // COPY TMPMIR UP TO MIRROR
			c[z] += 1; // ENUMERATE THE RESULT
		}
		print_real(mirror, "REAL mirror bottom of outer loop");
		print_real(c, "FAR BOTTOM  REAL STRING");
	}
	c[z] = '\0';
	print_real(c, "FAR BOTTOM  REAL STRING");
	return c;
}

