#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



/* function declarations */
char * add(char *, char *, char *);
char * addition(char *, char *, char *);
int getcharval2(const char *, size_t);
void flip_sign(void);
size_t reversestr(char *);
char * subtract(char *, char *, char *);
char * subtraction(char *, char *, char *);
char *multiply(const char *, const char *, char *);


/* globals */
char sign = '+';


/* functions */
int main(int argc, char *argv[])
{

        if ( argc != 3)
        {
                fprintf(stderr, "Needs two args\n");
                return 1;
        } 
	char *a = argv[1];
	char *b = argv[2];
	
	char *c;
	c = malloc(strlen(a) + strlen(b + 256));

	printf("\n\n");
        printf("         %20s\n", a);
        printf(" + and - %20s\n", b);
	printf("         %20s\n", "-------------------"); 


	c = add(a, b, c);
	printf("answer = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10));


	c = subtract(a, b, c);
	printf("answer = %20ld (subtraction) \n", strtol(a, 0, 10) - strtol(b, 0, 10));

	
	c = multiply(a, b, c);
	printf("result = %20s\n", c);
	printf("answer = %20ld (multiply) \n", strtol(a, 0, 10) * strtol(b, 0, 10));
	
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
int getcharval2(const char *s, size_t idx)
{
	size_t len = strlen(s);
        if (idx < len)
        	return s[len - idx - 1];
        return 48;
}


int getcharval(const char *s, size_t idx)
{ 
	size_t len = strlen(s);
        if (idx < len)
        	return s[len - idx - 1] - 48;
        return 0;
}


char * addition(char *a, char *b, char *c)
{
        
	size_t i = 0;
	size_t width = 0;
	size_t sum = 0;
	size_t carry = 0;
	size_t wa = strlen(a); 
	size_t wb = strlen(b); 
	char ca = 0;
	char cb = 0; 
        
	/* greatest width */
	if ( wa > wb ) width = wa;
	else width = wb;

	/* for arbitrary precision it makes sense to allocate for math libs */
	if (!(c = malloc (width)))
	{
		fprintf(stderr, "malloc failed\n"); return c;
	}
	
	c[0] = sign;
	++c;
	

        for(i=0; i<width; i++){
                ca = getcharval(a, i);
                cb = getcharval(b, i);
		//sum = a[wa - i - 1] + b[wb - i - 1] + carry - 48 - 48; 
                sum = ca + cb + carry;
		
                carry = 0;
                if(sum > 9){
                        carry = 1;
                        sum -= 10;
                }
                c[i] = sum + 48;
        }

        if (carry) 
		c[i++] = '1'; /* carry + 48 */

        c[i]= 0; 
        reversestr(c);
	--c;
	c[0] = sign;
        printf("result = %20s\n", c); 
	
	return c;

}


char * subtraction(char *a, char *b, char *c)
{


	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int borrow = 0;
	size_t wa = strlen(a); 
	size_t wb = strlen(b);
        char tens[1000] = { 0 };
        
	/* greatest width */
	if ( wa > wb ) width = wa;
	else width = wb;

	/* for arbitrary precision it makes sense to allocate for math libs */
	if (!(c = malloc (width + 1)))
	{
		fprintf(stderr, "malloc failed\n"); return c;
	} 
	
	c[0] = sign;
	++c;

        for(i=0; i<width; i++){ 
		//sum = a[wa - i - 1] - b[wb - i - 1] + borrow + 96; 
                sum = getcharval2(a, i) - getcharval2(a, i) + borrow + 96;
		
                borrow = 0;
                if(sum < 96){
                        borrow = -1;
                        sum +=10;
                }
                c[i] = sum - 48;
        }
	/*  Nothing left to borrow */
	if ( borrow == -1)
	{
		//printf("-");
		flip_sign();
		size_t z = width + 1;
		memset(tens, '0', z);
		tens[0] ='1';
		tens[z] ='\0';
		reversestr(c);
		c = subtraction(tens, c, c);
		return c;
	} 
        c[i]= 0; 
        reversestr(c); 
	if ( c[0] == '0' )
		++c;

	/* add the sign back in ... */
	--c;
	c[0] = sign;
	
        printf("result = %20s\n", c); 

	return c;
}


char * subtract(char *x, char *y, char *c)
{ 
	/* sign bits have a lot of possibilities and rules, this is incomplete */ 
	if (x[0] == '+')
		++x;
	if ( x[0] == '-' )
	{
		++x;
		flip_sign();
		c = add(x, y, c);
	}else if (y[0] == '+')
	{
		++y;
		c = subtraction(x, y, c);
	}
	else if (y[0] == '-')
	{ 
		++y;
		flip_sign();
		c = add(x, y, c);
		
	} else c = subtraction(x,y,c);

	return c;
}


char * add(char *x, char *y, char *c)
{ 
	if ( x[0] == '+')
		++x;
	if ( x[0] == '-' )
	{
		++x;
		flip_sign();
		c = subtract(x, y, c);
	}else if (y[0] == '+')
	{
		++y;
		c = addition(x, y, c);
	}
	else if (y[0] == '-')
	{ 
		++y;
		c = subtract(x, y, c); 
	}
	else c = addition(x, y, c);

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
	{
		++a;
		multiply(a, b, c);
		return c;
	}
	if(b[0] == '+')
	{
		++b;
		multiply(a, b, c);
		return c;
	}
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

