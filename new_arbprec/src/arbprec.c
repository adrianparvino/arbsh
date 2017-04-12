#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <arbprec/arbprec.h>

/* Functions */
void addition(int *a, int *b) 
{ 
	int i;
	int carry = 0;
	size_t width = 0;
	size_t wa = arraylen(a, 4242);
	size_t wb = arraylen(b, 4242);
	
	if ( wa > wb ) width = wa;
	else width = wb;

	for (i = width - 1; i>=0 ; i--)
	{
		a[i] += b[i] + carry;
		carry = 0;
		if (a[i] >= base)
		{
			carry = 1;
			a[i] -= base;
		}
	}
	if ( carry == 1 )
	{ 
		mirror[0] = 1;
		copyarray(mirror + 1, a);
		printarray(mirror, cardinal + 1); 
	}
}

int *addition_r(int *a, int *b, int *c)
{
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int carry = 0;

	
	size_t wa = arraylen(a, 4242);
	size_t wb = arraylen(b, 4242);

	if ( wa > wb ) width = wa;
	else width = wb;

        for( i = 0; i < width ; i++)
	{
		sum = getcharval(a, i) + getcharval(b, i) + carry;
                carry = 0;
                if(sum >= base){
                        carry = 1;
                        sum -= base;
                }
                c[i] = sum;
        }
        if (carry)
		c[i++] = 1;
        c[i] = 4242;
       
	reversestr(c);
	printarray(c, i);
	return c;
}

size_t arraylen(int *array, int delim)
{ 
	size_t len = 0; 
	while( array[len] != delim) 
		++len;
	return len;
}

void copyarray(int *answer, int *from)
{
	size_t i = 0;
	for( i = 0; i < cardinal; i++)
		answer[i] = from[i];
}

void die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
} 

int *divide(int *a, int *b, int *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0; 
	size_t numer = arraylen(a, 4242);	/* cardinality of the numerator */
	size_t denom = arraylen(b, 4242); 	/* cardinality of the denominator */
	size_t real_cardinality = 0;		/* cardinality of the quotient's real part */
	size_t imag_cardinality = 0;		/* cardinality of the quotient's imaginary part */
	int sum = 0; 				/* hold a temporary signed value <= base */
	int rec = 0; 				/* boolean record */

	/* TODO: capture the falling places and increment the *int */

	
	setarray(c, 0);
	setarray(mirror, 0);
	copyarray(mirror, a);
	setarray(tmpmir, 0);
	copyarray(tmpmir, mirror);

	/* numerator / denominator  =  quotient */
	for ( ; z < numer ; )
	{
		copyarray(tmpmir, mirror);
		for (rec = 0, i = 0, j = z; i < denom ; j++ ,i++) 
		{
			sum = (mirror[j]) - (b[i]);
			if ( sum < 0 )
			{
				if ( j == z )
				{
					mirror[j + 1] += ((mirror[j]) * base);
					++z;
				}
			 	else
				{
					mirror[j - 1] -= 1;
					mirror[j] += base;
				}
				rec = 1;
				break; 
			}
			tmpmir[j] = sum;
		} 
		if ( rec == 0 )
		{ 
			copyarray(mirror, tmpmir); 
			c[z] += 1;
		} 
		if ( iszero(tmpmir) == 0)
			break;
	}

	if ( numer + 1 > denom )
		real_cardinality = numer - denom + 1;
	else
		real_cardinality = z;

	if ( z >= real_cardinality )
		imag_cardinality = z - real_cardinality;
	
	printarray(c, real_cardinality);
	
	printarray(c + (real_cardinality) ,imag_cardinality); 
	return c;
}

int getcharval(int *s, size_t idx)
{ 
	size_t len = arraylen(s, 4242);
        if (idx < len)
        	return s[len - idx - 1];
        return 0;
} 

int iszero(int *answer)
{
	size_t i = 0;
	for ( i = 0; i < cardinal; i++)
		if ( answer[i] )
			return 1;
	return 0;
}

int *multiply(int *a, int *b, int *c)
{
	int i = 0;
	int j = 0;
	size_t k = 0;
	int sum = 0;
	int carry = 0;
	int la = 0;
	int lb = 0;
	/* either is zero, return c "0" ... */
 
	la = arraylen(a, 4242);
	lb = arraylen(b, 4242);
	memset(c, 0, 100);

	for ( i = la - 1; i >= 0 ; i--)
	{
		for ( j = lb - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--) 
		{
			sum = (a[i]) * (b[j]) + (c[k]) + carry;
			carry = sum / base;
			c[k] = (sum % base); 
		}
		c[k] += carry; 
	}
	printarray(c, la + lb); 
	return c;
}

void printarray(int *a, size_t len)
{
	size_t i = 0;
	for ( i = 0; i < len ; )
		printf("%d", a[i++]);
	printf("\n");
} 

size_t reversestr(int *x)
{
        size_t i = 0;
        char swap = 0;
        size_t lim = arraylen(x, 4242);
        size_t half = lim / 2;

        for ( ; i < half ; i++)
        {
                swap = x[i];
                x[i] = x[lim - i - 1];
                x[lim - i - 1] = swap;
        }
        return lim;
}

void setarray(int *answer, int rootcap)
{
	size_t i = 0;
	for( i = 0; i < cardinal; i++)
		answer[i] = 0;
	answer[0] = rootcap;
}
 
void set_array(int *array, int init, size_t dec, int sign, int terminator, size_t len)
{
	/* set_array(array, 0, 0, '+', 4242, 4099); */
	size_t i = 2;
	for( i = 2; i < len; i++)
		array[i] = init;
	array[0] = dec;
	array[1] = sign;
	array[len] = terminator;
}

void short_divide(int *answer, int denom)
{
	int carry = 0;
	size_t i = 0;
	for( i = 0; i < cardinal; i++)
	{
		answer[i] += carry * base;
		carry = answer[i] % denom;
		answer[i] /= denom;
	}
}

void short_multiply(int *answer, int factor)
{
	int i;
	int carry = 0;
	for ( i = cardinal - 1; i >= 0 ; i--)
	{
		answer[i] *= factor;
		answer[i] += carry;
		carry = answer[i] / base;
		answer[i] %= base;
	}
}

int *str2ints(char *a, int *b)
{
	size_t i = 0;
	size_t tot = 0;
	while ( a[i] != '\0' )
	{
		b[i] = a[i] - '0';
		++i;
		++tot;
	}
	if ( tot > cardinal )
		cardinal = tot;
	return b;
}

void *strallocate(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		die("malloc failed\n"); 
	return ret;
}

void subtract(int *answer, int *decrem)
{
	int i;
	int isneg = 0;
	size_t width = 0;
	
	size_t wa = arraylen(answer, 4242); 
	size_t wb = arraylen(decrem, 4242);

	if ( wa > wb ) width = wa;
	else width = wb;

	copyarray(mirror, answer);
	for ( i = width; i >= 0 ; i--)
	{ 
		answer[i] -= decrem[i];
		mirror[i] -= decrem[i]; 
		isneg = 0;
		if ( answer[i] < 0 )
		{
			answer[i] += base;
			answer[i - 1]--;
			isneg = 1;
		}
		if ( mirror[i] < 0 )
		{
			mirror[i] += base ;
			mirror[i] = base - mirror[i];
		} 
	}
	if ( isneg == 1 )
	{
		verbosity(mirror, "was negative", 0);
		copyarray(answer, mirror);
	}
}

int *subtraction_r(int *a, int *b, int *c)
{ 
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int mir = 0;
	int borrow = 0;
	int carry = -1;
	size_t wa = arraylen(a, 4242); 
	size_t wb = arraylen(b, 4242);

	if ( wa > wb ) width = wa;
	else width = wb;

        for( i=0; i < width ; i++)
	{
		sum = getcharval(a, i) - getcharval(b, i) + borrow; 
		mir = getcharval(a, i) - getcharval(b, i) + carry;
                carry = borrow = 0;
		if(sum < 0)
		{
                        borrow = -1;
                        sum += base; 
                }
		if(mir < 0)
		{
                        carry = -1;
                        mir += base; 
                } 
		c[i] = sum;
		mirror[i] = (base-1) - mir;
        }
	
        c[i] = mirror[i] = 4242; 
	if (borrow == -1)
		c = mirror;

	reversestr(c);
	printarray(c, i );
	return c;
} 

void verbosity(int *array, char *message, int on)
{
	static int verbose = 0;
	if ( on == 1 )
		verbose = 1;
	if ( verbose == 0 )
		return;
	printf("Verbosity message: %s\n", message);
	
	printarray(array, cardinal);
	printf("END verbosity:\n");
}
