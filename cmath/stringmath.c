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

/* globals */
static char *mirror;


/* functions */
int main(int argc, char *argv[])
{

        if ( argc != 3) 
                die("Please provide two numbers"); 
	/* lots of magic with pointers to avoid using memmove */
	char *a = argv[1];
	char *b = argv[2];
	size_t len = (strlen(a) + strlen(b) + 10);
	char *d;
	char *z;
	char *y;

	d = strallocate(len);
	mirror = strallocate(len);
	z = mirror;
	y = d;
	/*  */
	

	printf("\n\n");
        printf("         %20s\n", a);
        printf("  +,-,*  %20s\n", b);
	printf("         %20s\n", "-------------------");

	/* test functions against strtol ( only checks first 19 digits ) */
	//memset(d, 0, len);
	d[0] = 0;
	d = add(a, b, d);
	printf("result(add) = %20s\n", d); 
	printf("answer      = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10));

	//memset(d, 0, len);
	d[0] = 0;
	d = subtract(a, b, d);
	printf("result(sub) = %20s\n", d);
	printf("answer      = %20ld (subtraction) \n", strtol(a, 0, 10) - strtol(b, 0, 10));

	//memset(d, 0, len);
	d[0] = 0;
	d = multiply(a, b, d);
	printf("result(mul) = %20s\n", d);
	printf("answer      = %20ld (multiplication) \n", strtol(a, 0, 10) * strtol(b, 0, 10));

	//memset(d, 0, len);
	//d[0] = 0;
	//d = division(i, j, d);
	//printf("result(div) = %20s\n", d);
	//printf("answer      = %20lf (division) \n", strtod(a, 0) / strtod(b, 0));
	/* */
	free(d = y);
	free(mirror = z);
	/* */
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
	/* reverse a string and return its length */
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


/* slow but could easily be made faster by passing in known string lengths */
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
	//c++;

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

	/* greatest width */
	if ( wa > wb ) width = wa;
	else width = wb; 
	
	setsign(c++);
	//c++;
	*mirror = '\0';
	setsign(mirror++);
	//mirror++;

	/* subtract */
        for( i=0; i < width ; i++)
	{ 
		/* adding addition in here would save code but waste memory */
		sum = getcharval(a, i) - getcharval(b, i) + borrow; 
		mir = getcharval(a, i) - getcharval(b, i) + carry;
	
                borrow = 0;
		if(sum < 0)
		{
                        borrow = -1;
                        sum += 10; 
                }
		carry = 0;
		if(mir < 0)
		{
                        carry = -1;
                        mir += 10; 
                } 
		c[i] = sum + 48;
		mirror[i] = '9' - mir;
		//printf("c      =    %s ....   \n", c);
		//printf("mirror =    %s ....   \n", mirror);
		
		//printf("c      =    %s ....   \n", c -1 );
		//printf("mirror =    %s ....   \n", mirror - 1);
        }
	/* '\0' cap */
        c[i] = mirror[i] = '\0';
	//printf("carry  = %d\n", carry);
	//printf("borrow = %d\n", borrow);
	if (borrow == -1) /// then use the symmetrical mirror 
	{
		//setsign(mirror - 1);
		c = mirror;
		//printf("was here\n");
		if (!(*(a-1) == '-' && *(b-1) == '-'))
		setsign(c - 1);
		
	}
	/* reverse result */
        reversestr(c--);
	/* pass the pointer back to the caller */
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

	
	//printf("subtract 0\n");
	if (x[0] == '+')
		++x; 
	if (y[0] == '+')
		++y;
	if (x[0] == '-' && y[0] == '-')
	{
		setsign(c);
		*mirror = '\0';
		setsign(mirror);
		//setsign(mirror);
		//setsign(c);
		//printf("subtract 1\n");
		return c = subtraction(x + 1, y + 1, c);
	} 
	else if (x[0] == '-')
	{
		//printf("subtract 2\n");
		setsign(c);
		*mirror = '\0';
		setsign(mirror);
		return c = addition(x + 1, y, c);
	}
	else if (y[0] == '-')
	{ 
		//printf("subtract 3\n");
		return c = addition(x, y + 1, c); 
	} else {
		
		c = subtraction(x, y, c);
	
	}
	
	//printf("subtract 4\n");
	return c;
}


char * add(char *x, char *y, char *c)
{

	printf("add 0\n");
	if (x[0] == '+')
		++x; 
	if (y[0] == '+')
		++y;

	if ( x[0] == '-' && y[0] == '-' )
	{
		//printf("add 1\n");
		setsign(c);
		return c = addition(x + 1, y + 1, c);
		//return c = subtraction(x + 1, y + 1, c);
	} 
	else if (x[0] == '-')
	{ 
		//printf("add 2\n");
		setsign(c);
		setsign(c);
		//setsign(mirror);
		return c = subtraction(y, x + 1, c);
	}
	else if (y[0] == '-')
	{
		//printf("add 3\n");
		return c = subtraction(x, y + 1, c);
	} else c = addition(x, y, c);
	//printf("add 4\n");
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
