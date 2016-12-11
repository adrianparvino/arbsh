#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
	2016 CM Graff "stringmath.c"
	See stringmath.txt for documentation.  
*/

/* function declarations */
char *add(char *, char *, char *);
char *addition(char *, char *, char *);
void die(char *);
char *division(char *, char *, char *);
int getcharval(char *, size_t);
char *multiply(char *, char *, char *);
void print_real(char *, char *);
size_t reversestr(char *);
void setsign(char *);
void *strallocate(size_t);
char *subtract(char *, char *, char *);
char *subtraction(char *, char *, char *);


/* globals */
static char *mirror; 
static char *tempmir;
int verbosity = 0;


/* functions */
int main(int argc, char *argv[])
{
	int o = 0;
	while ((o = getopt (argc, argv, "v")) != -1)
                switch (o) { 
			case 'v': 
				verbosity = 1;
                                break; 
                        default: 
				break;
                }

        argv += optind;
        argc -= optind;

	
	if ( argc < 2) 
		die("Please provide two numbers\n"); 

	char *a = argv[0];
	char *b = argv[1];
	size_t len = (strlen(a) + strlen(b) + 10);
	char *d;
	char *z;
	char *y;

	y = d = strallocate(len);
	z = mirror = strallocate(len);
	tempmir = strallocate(len);

	printf("\n\n");
        printf("         %20s\n", a);
        printf("+,-,*,/  %20s\n", b);
	printf("         %20s\n", "-------------------");



	d[0] = 0;
	d = add(a, b, d);
	printf("result(add) = %20s\n", d); 
	printf("answer      = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10)); 
	
	d[0] = 0;
	d = subtract(a, b, d);
	printf("result(sub) = %20s\n", d);
	printf("answer      = %20ld (subtraction) \n", strtol(a, 0, 10) - strtol(b, 0, 10)); 

	d[0] = 0;
	d = multiply(a, b, d);
	printf("result(mul) = %20s\n", d);
	printf("answer      = %20ld (multiplication) \n", strtol(a, 0, 10) * strtol(b, 0, 10));

	d[0] = 0;
	d = division(a, b, d);
	printf("result(div) = %s\n", d);
	printf("answer      = %lf (division) \n", strtod(a, 0) / strtod(b, 0));

	free(d = y);
	free(mirror = z);
	free(tempmir);
} 

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
        size_t lim = strlen(x);
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
	printf("------------------------\n");
	printf("name:      %s\n", realname);
	printf("string:    %s\n", s);
	printf("real nums: ");
	
	while (s[i] != '\0')
	{
		printf("|%d", s[i] - '0');
		++i;
	}
	printf("|\n");
	printf("------------------------\n");
}

int getcharval(char *s, size_t idx)
{ 
	size_t len = strlen(s);
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
	size_t wa = strlen(a); 
	size_t wb = strlen(b); 

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
	size_t wa = strlen(a); 
	size_t wb = strlen(b);

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
	if (!strcmp(a, "0") || !strcmp(b, "0"))
	{ 
		c[0] = '0';
		c[1] = '\0';
		return c - 1;
	}
 
	la = strlen(a);
	lb = strlen(b);
	
	memset(c, '0', la + lb);
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
	if(!(ret = malloc(len)))
		die("malloc failed\n"); 
	return ret;
} 

void die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}


char *division(char *a, char *b, char *c)
{ 
	size_t i = 0;		// Increment over the divisors.
	size_t j = 0;		// Increment over the denominator.
	size_t z = 0;		// Increment through the answer.
	int sum = 0;		// Temporary sum to be evaluated, saves some evaluations.
	int norecord = 0;	// Boolean to control whether or not the answer is recorded.
	size_t denom = 0;	// Total number of digits in the denominator.
	size_t divisors = 0;	// Total number of digits in the divisor.
	divisors = strlen(b);	// Cardinality of the divisor.
	denom = strlen(a);	// Cardinality of the denominator.
	memset(c, '_', divisors + denom);	// Use Mayan zero shells to hold place values (for now).
	c[divisors + denom] = '\0';		// ASCII NUL cap the answer.
	
	memset(mirror, 0, divisors + denom);	// The mirror starts its life as a copy of the denominator,
	strcpy(mirror, a);			// otherwise the caller's denominator would be destroyed.
	memset(tempmir, 0, divisors + denom);	// But the mirror can't be modified with bad values,
	strcpy(tempmir, mirror);		// so we have a temporary copy of it too.

	// It's likely this could be reduced to one strcpy and some pointer swapping, but
	// for now we go ahead and strcpy each time there's a good value in the main loop
	
	for ( i = 0; z < denom ; ++i) // this works ok for some values but should be replaced by a BREAK
	{
		norecord = 0; // reset record
		strcpy(tempmir, mirror); // replace this with a pointer swap
		for (i =0,j=z; i < divisors ; j++,i++) // LOOP OVER DIVISORS
		{
			sum = (mirror[j]-'0') - (b[i]-'0'); // the actual work, everything else is carrying
			if ( sum < 0 ) // REVAL
			{	// HARD REVAL ( shift all ) // BAD
				if ( j == z ) // then REAL BAD we have a negative first position
				{	// and we need to carry the last value to the next transaction, a HARD REVAL 
					mirror[j + 1] += ((mirror[j] - '0') * 10); // FULL DIGIT CARRY (10 TO 90) 
					mirror[j] = '0'; // REMOVE ALL
					print_real(tempmir, "tempmir top HARD REVAL"); // VERBOSITY
					if ( c[z] == '_' ) 
						c[z] = '0';
					++z; // only HARD REVALS can change the place value
				}
				// SOFT REVAL ( borrow 10 )
				else // we have a negative non-first position and need to SOFT REVAL by borrowing.
				{    
					
					mirror[j - 1] -= 1; // REMOVE ONE 
					mirror[j] += 10;  // SINGLE TENS BORROW (ALWAYS TEN) 
					print_real(tempmir, "tempmir top SOFT REVAL"); // VERBOSITY
				}
				// either way we have to get out of here and not record the result 
				norecord = 1; // NO RECORD
				break;
			}
			// else was GOOD
			tempmir[j] = sum + '0';
			print_real(tempmir, "tempmir bottom GOOD"); // VERBOSITY
		} // if we leave the loop on our own, then RECORD it
		if ( norecord == 0 ) 
		{
			print_real(tempmir, "tempmir COPY CANDIDATE  RECORD"); // VERBOSITY
			strcpy(mirror, tempmir);  // any answer path that is not a REVAL is GOOD for incorporating into the mirror 
			if (c[z] == '_')
				c[z] = 48; // change the mayan shell to a zero 
			c[z] += 1; // any path that is not a REVAL is GOOD for enumerating the answer
		} 
		print_real(mirror, "REAL mirror"); // VERBOSITY
	}
	c[z] = '\0';
	print_real(c, "FAR BOTTOM  REAL STRING");
	return c;
}

