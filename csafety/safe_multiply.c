#include <stdio.h>

size_t safe_multiply(size_t i, size_t inc, size_t limit)
{ 
	if ( limit / i > inc ) 
	{
		fprintf(stderr, "Muliplication proposal was accepted\n");
		return i * inc;
	}
	fprintf(stderr, "Muliplication proposal was rejected, returning the limit\n");
	return limit;
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
