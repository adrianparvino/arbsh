#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	size_t i = 0;
	size_t limit = 10;
	
	for (; i < limit && i <(size_t)-1;++i)
		printf("Inside the hard bound loop \n");

	return 0;
}


