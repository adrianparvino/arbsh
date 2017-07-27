#include <stdlib.h>
#include <stdio.h> 

#define double_bound_loop(v,m,z) for(v=0; v<(m)&&v<(z); v++)

int main(void)
{
	size_t a;
	size_t b = 10;

	double_bound_loop(a, b, (size_t) -1) 
		printf("Inside the loop %zu\n", a);

	return 0;
}
