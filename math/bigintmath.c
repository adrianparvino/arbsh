#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


/* TODO: Short multiplication and division may work with floats given a few simple
	 modifications */

/* Function protoypes */
void addition(int *, int *);		/* Add integer arrays together */
int *addition_r(int *, int *, int *);	/* Add two arrays */
size_t arraylen(int *, int);		/* Similiar to strlen except it searches for the specified token */
void copyarray(int *, int *);		/* Copy an array of ints to another array of ints */ 
void die(char *);			/* Kill and error message */
int iszero(int *);			/* Returns true if an entire array is zero */ 
void short_divide(int *, int);		/* Divide an integer array by an integer */
int *divide(int *, int *, int *);	/* Multiply arrays of integers (long multiplication) */ 
void short_multiply(int *, int);	/* Multiply an integer array by an integer */
int *multiply(int *, int *, int *);	/* Multiply arrays of integers (long multiplication) */ 
size_t reversestr(int *);		/* Reverse an integer array */ 
void setarray(int *, int);		/* Set an array of ints to all zeros or a magnitude thereof */
void subtract(int *, int *);		/* Subtract an integer array from another */
int *subtraction_r(int *, int *, int *);/* Subtract two arrays */


/* More (helper) function prototypes */
int *str2ints(char *, int *);		/* Convert a string into an integer array */ 
void printarray(int *, size_t len);	/* Print an array of integers */
int getcharval(int *, size_t);		/* Return an indice position if it exists, if not, return 0 */
void verbosity(int *, char *);  /* Verbosity function */
void *strallocate(size_t);	/* Memory allocater with error */

/* Globals */
size_t cardinal;		/* All array functions must have the same length (cardinality) */
size_t carda;
size_t cardb;
int *bigint1;			/* Copy of argument 1 */
int *bigint2;			/* Copy of argument 2 */
int base = 10;			/* Default to base 10 */
int verbose = 0;		/* Verbosity boolean */
int *mirror;
int *result;
int *tmpmir;

/* Functions */
int main(int argc, char **argv)
{
	int *hold;	/* Copy of bigint1 */
	int *hold2;	/* Copy of bigint2 */
	double a = 0;
	double b = 0;
	int o = 0;
	

	while ((o = getopt (argc, argv, "vb:")) != -1)
		switch (o) { 
			case 'v':
				verbose = 1;
				break;
			case 'b': /* Override base */
				base = strtoul(optarg, 0, 10);
				break; 
			default: 
				break;
		}

	argv += optind;
	argc -= optind;


	if ( argc < 2 )
		die("Needs 2 args\n");

	a = strtod(argv[0], 0);
	b = strtod(argv[1], 0);

	printf("  %20lf\n", a);

	printf("  %20lf\n", b);
	printf("  %20s\n", "-------------------");
	printf("+ %20lf\n", a + b);
	printf("- %20lf\n", a - b);
	printf("* %20lf\n", a * b);
	printf("/ %20lf\n", a / b);
	

	mirror = strallocate(1000 * sizeof(int));
	result = strallocate(1000 * sizeof(int));
	tmpmir = strallocate(1000 * sizeof(int));
	bigint1 = strallocate(1000 * sizeof(int));
	bigint2 = strallocate(1000 * sizeof(int));

	/* arb divide */
	printf("division\n");
	carda = strlen(argv[0]);
	cardb = strlen(argv[1]);
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold[carda] = 4242;
	hold2[cardb] = 4242;
	divide(hold, hold2, result);

	/* arb multiply */
	printf("multiplication\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	multiply(hold, hold2, result);

	/* arb addition */
	printf("addition\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold = addition_r(hold, hold2, result);
	printarray(hold, cardinal);
	
	/* arb subtraction */
	printf("subtraction\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold = subtraction_r(hold, hold2, result);
	printarray(hold, cardinal);
	
	/* arb addition */
	printf("simple addition\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	addition(hold, hold2);
	printarray(hold, cardinal);

	/* arb subtract */
	printf("simple subtraction\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	subtract(hold, hold2);
	printarray(hold, cardinal);
	
	/* arb setarray, arb iszero, arb copyarray */
	printf("setarray. iszero, copyarray\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	setarray(hold, 0);
	setarray(hold2, 1);
	printarray(hold, cardinal);
	printarray(hold2, cardinal);
	if ( iszero(hold) == 0 )
		printf("hold is zero\n");
	if ( iszero(hold2) != 0 )
		printf("hold2 is not zero\n");
	copyarray(hold2, hold);
	if ( iszero(hold2) == 0 )
		printf("hold2 is now zero\n");

	/* single digit arb multiplication */
	printf("short multiplication\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	short_multiply(hold, hold2[0]);
	printarray(hold, cardinal);
	
	/* single digit arb short_short_divide */
	printf("short division\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	short_divide(hold, hold2[0]);
	printarray(hold, cardinal);

	return 0;
} 

void die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
} 

void printarray(int *a, size_t len)
{
	size_t i = 0;
	for ( i = 0; i < len ; )
		printf("%d ", a[i++]);
	printf("\n");
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

void verbosity(int *array, char *message)
{
	if ( verbose == 0 )
		return;
	printf("Verbosity message: %s\n", message);
	
	printarray(array, cardinal);
	printf("END verbosity:\n");
}

void *strallocate(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		die("malloc failed\n"); 
	return ret;
}

int getcharval(int *s, size_t idx)
{ 
	size_t len = arraylen(s, 4242);
        if (idx < len)
        	return s[len - idx - 1];
        return 0;
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

void copyarray(int *answer, int *from)
{
	size_t i = 0;
	for( i = 0; i < cardinal; i++)
		answer[i] = from[i];
}

size_t arraylen(int *array, int delim)
{ 
	size_t len = 0; 
	while( array[len] != delim) 
		++len;
	return len;
}

int iszero(int *answer)
{
	size_t i = 0;
	for ( i = 0; i < cardinal; i++)
		if ( answer[i] )
			return 1;
	return 0;
}

void setarray(int *answer, int rootcap)
{
	size_t i = 0;
	for( i = 0; i < cardinal; i++)
		answer[i] = 0;
	answer[0] = rootcap;
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
 
	la = carda;
	lb = cardb;
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
	printarray(c, carda + cardb); 
	return c;
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

int *divide(int *a, int *b, int *c)
{
	size_t i = 0;	
	size_t j = 0;
	size_t z = 0;

	size_t numer = carda;
	size_t denom = cardb;
	size_t left = numer; 

	int sum = 0;
	int rec = 0;

	/* numerator / denominator */
	setarray(c, 0);
	setarray(mirror, 0);
	copyarray(mirror, a);
	setarray(tmpmir, 0);
	copyarray(tmpmir, mirror);

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
					mirror[j] = 0;
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
		
	//	if ( iszero(tmpmir) == 0)
	//		break;
	} 
	printarray(c, z + 1); 
	return c;
}

void addition(int *a, int *b) 
{ 
	int i;
	int carry = 0;
	size_t width = 0;
	size_t wa = carda;
	size_t wb = cardb;
	
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
			//a[i - 1]++;
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
	size_t wa = carda;
	size_t wb = cardb;

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
		verbosity(mirror, "was negative");
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
