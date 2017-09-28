#include <stdio.h>

/*
	The C standard specifies that unsigned integer types must wrap around
	when they hit their maximum limit. However it is possible to keep this
	from happening by carefully precomputing each calculation to see that
	it can fit. The limit of a given size is computed with (T)-1. Presented 
	below is an idea for safe bounded multiplication.
	
*/
size_t safe_multiply(size_t i, size_t x, size_t lim)
{
	if (i == 0) /* Handle zero */
		return 0;
	if (lim / i >= x ) 
	{
		fprintf(stderr, "Multiplication proposal accepted\n");
		return i * x;
	}
	fprintf(stderr, "Multiplication proposal rejected\n");
	return lim;
}

int main(void)
{
	size_t a = (size_t) -1; 
	a = safe_multiply(a, 123123, (size_t) -1); 
	printf("%zu\n", a);

	a = (size_t) -1 / 10;
	a = safe_multiply(a, 123123, (size_t) -1);
	printf("%zu\n", a);

	unsigned int b = (unsigned int) -1;
	b = safe_multiply(b, 123123, (unsigned int) -1);
	printf("%u\n", b); 

	b = 500;
	b = safe_multiply(b, 1000000, (unsigned int) -1);
	printf("%u\n", b);
	
	b = (unsigned int) -1;
	b = safe_multiply(b, b - 123, (unsigned int) -1);
	printf("%u\n", b);

	return 0;
}
