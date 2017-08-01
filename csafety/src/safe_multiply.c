#include <stdio.h>

/*
	over an unsigned domain, (x * y) / y != x precisely captures "x*y overflows"
	as does a>-1U/b ? -1U : a*b;
*/

unsigned foo(unsigned a, unsigned b)
{
	return a>-1U/b ? -1U : a*b;
}

size_t safe_multiply(size_t i, size_t x, size_t lim)
{
	if (i == 0) /* Handle zero so that a "divide by zero" can't happen */
		return 0;
	if (lim / i >= x ) 
	{
		fprintf(stderr, "Muliplication proposal was accepted\n");
		return i * x;
	}
	fprintf(stderr, "Muliplication proposal was rejected, returning the limit\n");
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

	b = (unsigned int) -1 / 10;
	b = safe_multiply(b, 123123, (unsigned int) -1);
	printf("%u\n", b);
	
	b = 25;
	b = safe_multiply(b, 4, (unsigned int) -1);
	printf("%u\n", b);

	b = 500;
	b = safe_multiply(b, 1000000, (unsigned int) -1);
	printf("%u\n", b);
	
	b = (unsigned int) -1;
	b = safe_multiply(b, b - 123, (unsigned int) -1);
	printf("%u\n", b);

	return 0;
}
