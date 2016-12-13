#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

/* Function protoypes */
void addition(int *, int *);	/* Add integer arrays together */
void copyarray(int *, int *);	/* Copy an array of ints to another array of ints */
void die(char *);		/* Kill and error message function */
void short_divide(int *, int);	/* Divide an integer array by an integer */
int iszero(int *);		/* Returns true if an entire array is zero */
void short_multiply(int *, int);	/* Multiply an integer array by an integer */
void printarray(int *, size_t len);	/* Print an array of integers */
void setarray(int *, int);	/* Set an array of ints to all zeros or a magnitude thereof */
int *str2ints(char *, int *);	/* Convert a string into an integer array */
void subtract(int *, int *);	/* Subtract an integer array from another */
void verbosity(int *, char *);  /* Verbosity function */
void *strallocate(size_t);	/* Memory allocater with error */

/* Globals */
size_t cardinal;		/* All array functions must have the same length (cardinality) */
int *bigint1;			/* Copy of argument 1 */
int *bigint2;			/* Copy of argument 2 */
int base = 10;			/* Default to base 10 */
int verbose = 0;		/* Verbosity boolean */
int *mirror;

/* Functions */
int main(int argc, char **argv)
{
	int *hold;	/* Copy of bigint1 */
	int *hold2;	/* Copy of bigint2 */
	int o = 0;
	int d = 2;

	while ((o = getopt (argc, argv, "vb:d:")) != -1)
		switch (o) { 
			case 'v': /* Set verbose (not yet implemented) */
				verbose = 1;
				break;
			case 'b': /* Override base */
				base = strtoul(optarg, 0, 10);
				break; 
			
			case 'd': /* Set the short_divide and short_multiply test integer  */
				d = strtoul(optarg, 0, 10);
				break; 
			default: 
				break;
		}

	argv += optind;
	argc -= optind;


	if ( argc < 2 )
		die("Needs 2 args\n");

	mirror = strallocate(1000 * sizeof(int));

	/* arb addition */
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	addition(hold, hold2);
	printarray(hold, cardinal);

	/* arb subtract */
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	subtract(hold, hold2);
	printarray(hold, cardinal);
	
	/* arb setarray, arb iszero, arb copyarray */
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
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	short_multiply(hold, d);
	printarray(hold, cardinal);
	
	/* single digit arb short_short_divide */
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	short_divide(hold, d);
	printarray(hold, cardinal);

	return 0;
} 

void addition(int *answer, int *increm) 
{
	/* TODO: add swap to mirror if carry */
	/* TODO: replace int with size_t */
	int i;
	int needsmag = 0;
	for (i = cardinal - 1; i>=0 ; i--)
	{
		answer[i] += increm[i];
		needsmag = 0;
		if (answer[i] >= base)
		{
			needsmag = 1;
			answer[i] -= base;
			answer[i - 1]++;
		}
	}
	if ( needsmag == 1 )
	{ 
		mirror[0] = 1;
		copyarray(mirror + 1, answer);
		printarray(mirror, cardinal + 1); 
	}
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

int iszero(int *answer)
{
	/* TODO: write a similiar routine which checks if a number has neg vals */
	/* if it does have neg vals, then use a seed denominator to readjust it */
	size_t i = 0;
	for ( i = 0; i < cardinal; i++)
		if ( answer[i] )
			return 1;
	return 0;
}

void short_multiply(int *answer, int factor)
{
	/* ~= infinity * ( INT_MAX / 2 ) */
	if ( factor > INT_MAX / 2 )
		die("factor too big\n");

	/* TODO: Add support for multiple digit factors */
	/* TODO: Change incrementor to a size_t */
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

void printarray(int *a, size_t len)
{
	/* TODO: Use only 1 write (concatenate '\n') */
	size_t i = 0;
	for ( i = 0; i < len ; )
		printf("%d ", a[i++]);
	printf("\n");
}

void setarray(int *answer, int rootcap)
{
	/* TODO: add an end cap value */
	/* TODO: Formalize as a bigint creation / initialization function */

	size_t i = 0;
	for( i = 0; i < cardinal; i++)
		answer[i] = 0;
	answer[0] = rootcap;
} 

int *str2ints(char *a, int *b)
{
	/* TODO: Move strallocate out of this function */
	size_t i = 0;
	size_t tot = 0;
	size_t len = strlen(a);
	
	b = strallocate(len * sizeof(int));
	
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

void subtract(int *answer, int *decrem)
{
	/* TODO: replace int with size_t */
	int i;
	int isneg = 0;
	
	copyarray(mirror, answer);
	for ( i = cardinal - 1; i >= 0 ; i--){
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
		copyarray(answer, mirror); // This could be replaced by a pointer swap
	}
}

void verbosity(int *array, char *message)
{
	/* support message types from stringmath.txt too */
	if ( verbose == 0 )
		return;
	printf("Verbosity message: %s\n", message);
	
	printarray(array, cardinal);
	printf("END verbosity:\n");
}

void *strallocate(size_t len)
{
	/* TODO: Incorporate perror */
	void *ret;
	if(!(ret = malloc(len)))
		die("malloc failed\n"); 
	return ret;
}


