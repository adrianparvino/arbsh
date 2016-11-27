#include <stdio.h>

void string_mult(char *, char *);

void add(char *, char *);

char result[1000] = { 0 };

int main(int argc, char *argv[])
{
	if ( argc != 3)
	{
		fprintf(stderr, "Needs two args\n");
		return 1;
	}

	//size_t lena = strlen(argv[1]);
	//size_t lenb = strlen(argv[2]);

	add(argv[1], argv[2]);
	printf("result = %s\n", result);
	

	return 0;
}

void add(char *x, char *y)
{
	/* first number */
	/* strcpy( result, x); */
	size_t i = 0;
	while (x[i] != '\0' )
	{
		result[i] = x[i];
		i++; 
	}
	size_t len = i;
	

	/* second number */
}

void string_mult(char *x, char *y)
{
}
