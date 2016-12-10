#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* function declarations */
char *add(char *, char *, char *);
char *addition(char *, char *, char *);
void die(char *);
int getcharval(char *, size_t);
char *multiply(char *, char *, char *);
char *multiply2(const char *, const char *, char *);
size_t reversestr(char *);
void setsign(char *);
void *strallocate(size_t);
char *subtract(char *, char *, char *);
char *subtraction(char *, char *, char *); 


char *division(char *, char *, char *); 

void print_real(char *);


/* globals */
static char *mirror; 
static char *tempmir;

/* functions */
int main(int argc, char *argv[])
{

        if ( argc != 3) 
                die("Please provide two numbers"); 

	char *a = argv[1];
	char *b = argv[2];
	size_t len = (strlen(a) + strlen(b) + 10);
	char *d;
	char *z;
	char *y;

	y = d = strallocate(len);
	z = mirror = strallocate(len);
	tempmir = strallocate(len);

	printf("\n\n");
        printf("         %20s\n", a);
        printf("  +,-,*  %20s\n", b);
	printf("         %20s\n", "-------------------");

	/*
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
	*/

	d[0] = 0;
	d = division(a, b, d);
	printf("result(div) = %20s\n", d);
	printf("answer      = %20lf (division) \n", strtod(a, 0) / strtod(b, 0));

	//free(d = y);
	//free(mirror = z); 
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
	// divisor digit
	size_t i = 0;
	// denominator position or offest
	size_t j = 0;
	// result digits
	size_t k = 0;
	// position of transforming mirror
	size_t z = 0;

	int sum = 0;
	int carry = 0;
	int borrow = 0;
	int la = 0;
	int lb = 0;
	// total number of digits in the denominator
	size_t denom = 0;
	// total number of digits in the divisor
	size_t divisors = 0;

	// carry values over and adding them to the next position in order to produce
	// a result which is ranged from between 0-9

	// the mirror starts its life as a copy of the denominator

	divisors = strlen(b);
	denom = strlen(a);

	memset(c, 48, divisors + denom);

	c[divisors + denom] = '\0';
	printf("result1 %s\n", c); 

	int num1 = 0;
	int num2 = 0;
	strcpy(mirror, a);

	printf("%s\n", mirror);

	int norecord = 0;

	// concentrate on getting the division charts to display correctly
	// then find the pattern and add the tracking array as c[]

	for ( i = 0; z < denom ; ++i)
	{
		norecord = 0;
		strcpy(tempmir, mirror);
		for (i =0,j=z; i < divisors ; j++,i++) 
		{
			num1 = (tempmir[j]-'0');
			num2 = (b[i]-'0');

			sum = num1 - num2 + carry;
			carry = 0;
			if ( sum < 0 )
			{ 
				if ( j == z ) // then BAD we have a negative first position
				{ // and we need to carry the last value to the next transaction, and HARD REVAL
				  // sadly. no one knows what a HARD REVAL is, so that's a problem
					if ( j > 0 ) 
					{
						mirror[j + 1] += (mirror[j] * 10);
						mirror[j] -= 1;
						//mirror[j] = '0';
					}
					printf("BAD\n");
					++z;
				}
				else // we have a negative non-first position and need to REVAL by borrowing.
				{   
					mirror[j-1] -= 1;
					mirror[j] += 10;
					printf("REVAL\n");
				}
				// either way we have to get out of here and not record the result
				norecord = 1;
				break;
			}
			//sum = (a[i]-'0') / (b[j]-'0') - (c[k]-'0')+ carry; 

			tempmir[j] = sum + '0';

			printf("%s\n", tempmir);
			printf("tempmir:\n");
			print_real(tempmir);
			// strcpy(tempmir, a);
		}
		
		if ( norecord == 0 )
			strcpy(mirror, tempmir);
		if ( norecord == 0 )
			c[z] += 1;
	
		printf("result %s\n", c);
		printf("real mirror:\n");
		print_real(mirror);
		printf("mirror end %s\n", mirror);
	
	}
	c[z] = '\0';
	printf("result %s\n", c);
	return c;
}

void print_real(char *s)
{
	size_t i = 0;
	printf("------------------------\n");
	printf("real: ");
	
	while (s[i] != '\0')
	{
		printf("|%d", s[i] - '0');
		++i;
	}
	printf("|\n");
	printf("------------------------\n");
}
