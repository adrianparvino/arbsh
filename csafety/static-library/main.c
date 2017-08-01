#include <stdio.h>
#include "animals.h"
int main(void)
{
	printf("Number of dogs %d\n", dogs);
	dogs = inc_dogs(dogs);
	printf("Number of dogs %d\n", dogs);

	return 0; 
}
