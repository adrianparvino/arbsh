#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Function protoypes */
void addition(int *, int *);	/* Add two integer arrays */
void copyarray(int *, int *);	/* Copy an array of ints to another array of ints */
void die(char *);		/* Kill and error message function */
void divide(int *, int);	/* Divide an integer array by a digit */
int iszero(int *);		/* Returns true if an entire array is zero */
void multiply(int *, int);	/* Multiply an integer array by a digit */
void printarray(int *, size_t len);	/* Print an array of integers */
void setarray(int *, int);		/* Set an array of ints to all zeros or a magnitude thereof */
int *str2ints(char *, int *);	/* Convert a string into an integer array */
void subtract(int *, int *);	/* Subtract two integer arrays */

/* Globals */
size_t cardinal;		/* All array functions must have the same cardinality (length) */
int *bigint1;			/* Copy of argument 1 */
int *bigint2;			/* Copy of argument 2 */
int base = 10;			/* Default to base 10 */
int verbosity = 0;		/* Verbosity boolean */

/* Functions */
int main(int argc, char **argv)
{
	int *hold;	/* Copy of bigint1 */
	int *hold2;	/* Copy of bigint2 */
	int o = 0;
	int d = 2;

	while ((o = getopt (argc, argv, "vb:d:")) != -1)
		switch (o) { 
			case 'v': /* Set verbosity (not yet implemented) */
				verbosity = 1;
				break;
			case 'b': /* Override base */
				base = strtoul(optarg, 0, 10);
				break; 
			
			case 'd': /* Set the division and multiplication test digit */
				d = strtoul(optarg, 0, 10);
				break; 
			default: 
				break;
		}

	argv += optind;
	argc -= optind;
	

	if ( argc < 2 )
		die("Needs 2 args\n");

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
	
	/* arb setarray ,arb iszero, arb copyarray */
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
	multiply(hold, d);
	printarray(hold, cardinal);
	
	/* single digit arb division */
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	divide(hold, d);
	printarray(hold, cardinal);

	return 0;
} 

void addition(int *answer, int *increm) 
{
	/* TODO: add test for additional '1' place */
	/* TODO: replace int with size_t */
	int i;
	for (i = cardinal - 1; i>=0 ; i--)
	{
		answer[i] += increm[i];
		if (answer[i] >= base)
		{
			answer[i] -= base;
			answer[i - 1]++;
		}
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

void divide(int *answer, int denom)
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
	size_t i = 0;
	for ( i = 0; i < cardinal; i++)
		if ( answer[i] )
			return 1;
	return 0;
}

void multiply(int *answer, int factor)
{
	int i, carry = 0;
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
	size_t i = 0;
	for( i = 0; i < cardinal; i++)
		answer[i] = 0;
	answer[0] = rootcap;
} 

int *str2ints(char *a, int *b)
{
	/* TODO: Move memory management to another function */
	size_t i = 0;
	size_t tot = 0;
	size_t len = strlen(a);
	b = malloc(len * sizeof(int));
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
	/* TODO: add a symmetrical mirror for negative results */
	/* TODO: replace int with size_t */
	int i;
	for ( i = cardinal - 1; i >= 0 ; i--){
		answer[i] -= decrem[i];

		if ( answer[i] < 0 )
		{
			answer[i] += base;
			answer[i - 1]--;
		}
	}
}

