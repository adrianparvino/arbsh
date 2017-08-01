#include <stdio.h>
#include "animals.h"
int main(void)
{ 
	printf("Number of dogs %d\n", dogs);
	printf("Number of swans %d\n", swans);
	printf("Number of frogs %d\n", frogs);
	dogs = inc_dogs(dogs);
	swans = inc_dogs(swans);
	frogs = inc_dogs(frogs); 
	printf("Number of dogs %d\n", dogs);
	printf("Number of swans %d\n", swans);
	printf("Number of frogs %d\n", frogs); 
	return 0; 
}
