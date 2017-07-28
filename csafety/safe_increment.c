#include <stdio.h>


size_t safe_increment(size_t i, size_t inc, size_t limit)
{
	if ((limit - inc) >= i)
	{
		fprintf(stderr, "arithmetic proposal was acceptable\n");
		return i + inc;
	}
	fprintf(stderr, "arithmetic proposal failed, returning the limit\n");
	return limit;
}

int main(void)
{
	size_t a = (size_t) -1; 
	a = safe_increment(a, 123123, (size_t) -1); 
	printf("%zu\n", a);


	a = (size_t) -1 / 10; 
	a = safe_increment(a, 123123, (size_t) -1); 
	printf("%zu\n", a);

	unsigned int b = (unsigned int) -1;
	b = safe_increment(b, 123123, (unsigned int) -1);
	printf("%u\n", b);

	b = (unsigned int) -1 / 10; 
	b = safe_increment(b, 123123, (unsigned int) -1);
	printf("%u\n", b);

	return 0;
}
