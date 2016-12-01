#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* function declarations */
void add(char *, char *);
void addition(char *, char *);
int getcharval2(const char *, size_t);
void flip_sign(void);
size_t reversestr(char *);
void subtract(char *, char *);
void subtraction(char *, char *);
void multiplication(char *, char *);
char *multiplication2(const char *, const char *, char *);

/* globals */
char *res;
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
	
	char *c = malloc(10000);

	printf("\n\n");
        printf("         %20s\n", a);
        printf(" + and - %20s\n", b);
	printf("         %20s\n", "-------------------"); 


	add(a, b);
	printf("answer = %20ld (addition) \n", strtol(a, 0, 10) + strtol(b, 0, 10));


	subtract(a, b);
	printf("answer = %20ld (subtraction) \n", strtol(a, 0, 10) - strtol(b, 0, 10));

	
	c = multiplication2(a, b, c);
	printf("result = %20s\n", c);
	//multiplication(a, b);
	//printf("result = %20s\n", res);
	printf("answer = %20ld (multiplication) \n", strtol(a, 0, 10) * strtol(b, 0, 10));
	
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


void addition(char *a, char *b)
{
        char *result;
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
	if (!(result = malloc (width)))
	{
		fprintf(stderr, "malloc failed\n"); return;
	}
	
	result[0] = sign;
	++result;
	

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
                result[i] = sum + 48;
        }

        if (carry) 
		result[i++] = '1'; /* carry + 48 */

        result[i]= 0; 
        reversestr(result);
	--result;
	result[0] = sign;
        printf("result = %20s\n", result); 
	
	free(result);

}

void subtraction(char *a, char *b)
{

	char *result;
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int borrow = 0;
	size_t wa = strlen(a); 
	size_t wb = strlen(b); 
	char ca = 0;
	char cb = 0;
	
        char tens[1000] = { 0 };
        
	/* greatest width */
	if ( wa > wb ) width = wa;
	else width = wb;

	/* for arbitrary precision it makes sense to allocate for math libs */
	if (!(result = malloc (width + 1)))
	{
		fprintf(stderr, "malloc failed\n"); return;
	} 
	
		result[0] = sign;
		++result;

        for(i=0; i<width; i++){
                ca = getcharval2(a, i);
                cb = getcharval2(b, i);
		//sum = a[wa - i - 1] - b[wb - i - 1] + borrow + 96; 
                sum = ca - cb + borrow + 96;
		
                borrow = 0;
                if(sum < 96){
                        borrow = -1;
                        sum +=10;
                }
                result[i] = sum - 48;
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
		reversestr(result);
		subtraction(tens, result);
		return;
	}
        //if (borrow == -1) result[i++] = '1'; /* borrow + 48 */ 
	//if (result[0] == '0') 
        result[i]= 0; 
	// result[0]= 0; 
        reversestr(result);


	if ( result[0] == '0' )
	{
		//sign -= 2;
		//flip_sign();
		++result;
	}
	
		
	--result;
	result[0] = sign;
	//--result;
        printf("result = %20s\n", result); 

}


void subtract(char *x, char *y)
{ 
	/* sign bits have a lot of possibilities and rules, this is incomplete */ 
	if (x[0] == '+')
		++x;
	if ( x[0] == '-' )
	{
		++x;
		flip_sign();
		add(x, y);
	}else if (y[0] == '+')
	{
		++y;
		subtraction(x, y);
	}
	else if (y[0] == '-')
	{ 
		++y;
		flip_sign();
		add(x, y);
		
	} else subtraction(x,y);
}

void add(char *x, char *y)
{ 
	if ( x[0] == '+')
		++x;
	if ( x[0] == '-' )
	{
		++x;
		flip_sign();
		subtract(x, y);
	}else if (y[0] == '+')
	{
		++y;
		addition(x, y);
	}
	else if (y[0] == '-')
	{ 
		++y;
		subtract(x, y); 
	}
	else addition(x, y);
	
}

void multiplication(char *a, char *b)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int n = 0;
	int carry = 0;
	int la = 0;
	int lb = 0;

	char *c = res;

	if(a[0] == '+')
	{
		++a;
		multiplication(a, b);
		return;
	}
	if(b[0] == '+')
	{
		++b;
		multiplication(a, b);
		return;
	}
	/* either is zero, return "0" */
	if (!strcmp(a, "0") || !strcmp(b, "0")) {
		c[0] = '0', c[1] = '\0';
		return;
	}
 
	/* see if either a or b is negative */
	if (a[0] == '-') { i = 1; k = !k; }
	if (b[0] == '-') { j = 1; k = !k; }
 
	/* if yes, prepend minus sign if needed and skip the sign */
	if (i || j) {
		if (k) c[0] = '-';
		//c = c + k;
		res = res + k;
		multiplication(a+i, b+j);
		return;
	}
 
	la = strlen(a);
	lb = strlen(b);
	
	memset(c, '0', la + lb);
	
	c[la + lb] = '\0';
 
#	define I(a) (a - '0')
	for (i = la - 1; i >= 0; i--) {
		for (j = lb - 1, k = i + j + 1, carry = 0; j >= 0; j--, k--) {
			/* summation of acquired terms is done as the multiplication builds places */
			n = I(a[i]) * I(b[j]) + I(c[k]) + carry;
			carry = n / 10;
			c[k] = (n % 10) + '0';
		}
		c[k] += carry;
	}
#	undef I

	//if ( c[0] == '0')
	//	++res;
 
	return;
}


char *multiplication2(const char *a, const char *b, char *c)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int n = 0;
	int carry = 0;
	int la = 0;
	int lb = 0;

	if(a[0] == '+')
	{
		++a;
		multiplication2(a, b, c);
		return c;
	}
	if(b[0] == '+')
	{
		++b;
		multiplication2(a, b, c);
		return c;
	}
	/* either is zero, return "0" */
	if (!strcmp(a, "0") || !strcmp(b, "0")) {
		c[0] = '0', c[1] = '\0';
		return c;
	}
 
	/* see if either a or b is negative */
	if (a[0] == '-') { i = 1; k = !k; }
	if (b[0] == '-') { j = 1; k = !k; }
 
	/* if yes, prepend minus sign if needed and skip the sign */
	if (i || j) {
		if (k) c[0] = '-';
		multiplication2(a + i, b + j, c + k);
		return c;
	}
 
	la = strlen(a);
	lb = strlen(b);
	memset(c, '0', la + lb);
	c[la + lb] = '\0';
 
#	define I(a) (a - '0')
	for (i = la - 1; i >= 0; i--) {
		for (j = lb - 1, k = i + j + 1, carry = 0; j >= 0; j--, k--) {
			n = I(a[i]) * I(b[j]) + I(c[k]) + carry;
			carry = n / 10;
			c[k] = (n % 10) + '0';
		}
		c[k] += carry;
	}
#	undef I

	if (*c == '0') 
		++c;
	
 
	return c;
}

