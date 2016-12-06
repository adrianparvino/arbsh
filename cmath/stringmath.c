#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* function declarations */
char *add(char *, char *, char *);
char *addition(char *, char *, char *);
void die(char *); 
void flip_sign(void);
int getcharval(char *, size_t);
char *multiply(const char *, const char *, char *); 
size_t reversestr(char *);
void *strallocate(size_t);
char *subtract(char *, char *, char *); 
char *subtraction(char *, char *, char *);


char *division(char *, char *, char *);


/* globals */
static char *mirror;
char sign = '+';

/* functions */
int main(int argc, char *argv[])
{

        if ( argc != 3) 
                die("Needs two args"); 
	/* lots of magic with pointers to avoid using memmove */
	char *a = argv[1];
	char *b = argv[2];
	size_t len = (strlen(a) + strlen(b) + 100);
	char *d = malloc(len);
	char *i = malloc(len);
	char *j = malloc(len);
	char *z;
	char *y = d;
	mirror = malloc(len);
	z = mirror;
	strcpy(i, a);
	strcpy(j, b);
	/*  */

	printf("\n\n");
        printf("         %20s\n", a);
        printf("  +,-,*  %20s\n", b);
	printf("         %20s\n", "-------------------");

	/* test functions against strtol ( only checks first 19 digits ) */
	memset(d, 0, len);
	d = add(i, j, d);
	printf("result(add) = %20s\n", d); 
	printf("answer      = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10));

	memset(d, 0, len);
	d = subtract(i, j, d);
	printf("result(sub) = %20s\n", d);
	printf("answer      = %20ld (subtraction) \n", strtol(a, 0, 10) - strtol(b, 0, 10));

	//memset(d, 0, len);
	//d = multiply(i, j, d);
	//printf("result(mul) = %20s\n", d);
	//printf("answer      = %20ld (multiplication) \n", strtol(a, 0, 10) * strtol(b, 0, 10));

	//memset(d, 0, len);
	//d = division(i, j, d);
	//printf("result(div) = %20s\n", d);
	//printf("answer      = %20lf (division) \n", strtod(a, 0) / strtod(b, 0));
	/* */
	free(i);
	free(j);
	free(d = y);
	free(mirror = z);
	/* */
} 


void flip_sign(void)
{
	if (sign =='-')
		sign = '+';
	else if (sign == '+')
		sign = '-'; 
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
		//return s[len - idx ] - 48;
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
        
	/* greatest width */
	if ( wa > wb ) width = wa;
	else width = wb;
	/* roll off the sign bit */
	*c++ = sign;
	
	/* add */
        for(i=0; i<width; i++)
	{ 
		sum = getcharval(a, i) + getcharval(b, i) + carry;
                carry = 0;
                if(sum > 9){
                        carry = 1;
                        sum -= 10;
                }
                c[i] = sum + 48;
        }
	/* Perform the final carry */
        if (carry) 
		c[i++] = '1';
	/* '\0' cap */
        c[i]= 0; 
	/* reverse result */
        reversestr(c);
	/* add the sign back in */
	
	*--c = sign;
	
	
	
	/* restore the sign bit for the next caller */
	sign = '+';
	/* pass the pointer back to the caller */
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

	/* roll off the sign bit */
	*c++ = sign; 
	


	/* subtract */
        for(i=0; i<width; i++)
	{ 
		/* adding addition in here would save code but waste memory */
		sum = getcharval(a, i) - getcharval(b, i) + borrow; 
		mir = getcharval(a, i) - getcharval(b, i) + carry;
	
                borrow = 0;
		if(sum < 0)
		{
                        borrow = -1;
                        sum +=10; 
                }
		carry = 0;
		if(mir < 0 )
		{
                        carry = -1;
                        mir +=10; 
                } 
		c[i] = sum + 48;
		mirror[i] = '9' - mir;
        }

	/* '\0' cap */
        c[i] = mirror[i] = 0;
	
	if ( borrow == -1) // then use the symmetrical mirror 
	{
		//c = mirror;
		flip_sign();
		reversestr(mirror);
		*--c = sign;
		sign = '+';
		return mirror;
	}

	/* reverse result */
        reversestr(c);
	/* add the sign back in ... */
	*--c = sign;
	
	
	
	/* restore the sign bit for the next caller */
	sign = '+';
	/* pass the pointer back to the caller */
	return c;
}


char *multiply(const char *a, const char *b, char *c)
{

	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;
	int la = 0;
	int lb = 0;

	/* if a or b has a positive sign then dispose of it */
	if(a[0] == '+') 
		return multiply(++a, b, c);
	if(b[0] == '+') 
		return multiply(a, ++b, c);
		
	/* either is zero, return c "0" */
	if (!strcmp(a, "0") || !strcmp(b, "0")) {
		c[0] = '0'; c[1] = '\0';
		return c;
	}
 
	/* see if either a or b is negative */
	if (a[0] == '-') { i = 1; k = !k; }
	if (b[0] == '-') { j = 1; k = !k; }
 
	/* if yes, prepend minus sign if needed and skip the sign */
	if (i || j) {
		if (k) c[0] = '-';
			multiply(a + i, b + j, c + k);
		return c;
	}
 
	la = strlen(a);
	lb = strlen(b);
	
	memset(c, '0', la + lb);
	c[la + lb] = '\0'; 

	for (i = la - 1; i >= 0; i--) 
	{ 
		for (j = lb - 1, k = i + j + 1, carry = 0; j >= 0; j--, k--) 
		{ 
			sum = (a[i]-'0') * (b[j]-'0') + (c[k]-'0') + carry;
			carry = sum / 10;
			c[k] = (sum % 10) + '0'; 
		}
		c[k] += carry; 
	}

	if (*c == '0') 
		++c;
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
	if ( x[0] == '-' && y[0] == '-' )
	{ 
		return c = subtraction(x + 1, y + 1, c);
	} 
	else if (x[0] == '-')
	{ 
		flip_sign(); 
		return c = addition(x + 1,y,c);
	}
	else if (y[0] == '-')
	{ 
		return c = addition(x,y +1,c); 
	} else c = subtraction(x,y,c);
	
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
		return c = subtraction(x + 1, y + 1, c);
	} 
	else if (x[0] == '-')
	{ 
		flip_sign();
		return c = subtraction(x + 1,y,c);
	}
	else if (y[0] == '-')
	{
		return c = subtraction(x,y + 1,c);
	} else c = addition(x,y,c);
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
	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;
	int la = strlen(a);
	int lb = strlen(b);
	
	memset(c, '0', la + lb);
	c[la + lb] = '\0'; 

	for (i = 0; i <= la; i++) 
	{ 
		carry = 0;
		for (j = 0 , k = i; j <= lb; j++, k++) 
		{ 
			sum = (a[i]-'0') / (b[j]-'0') + (c[k]-'0') + carry;
			carry = sum * 10;
			c[k] = (sum % 10) + '0'; 
		}
		c[k] -= carry; 
	}

	if (*c == '0') 
		++c;
	return c;
}

