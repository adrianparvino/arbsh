#include <stdio.h>
#include "animals.h"
int main(void)
{ 
	printf("Number of dogs %d\n", dogs);
	printf("Number of swans %d\n", swans);
	printf("Number of frogs %d\n", frogs);
	dogs = inc_dogs(dogs);
	swans = inc_swans(swans);
	frogs = inc_frogs(frogs); 
	printf("Number of dogs %d\n", dogs);
	printf("Number of swans %d\n", swans);
	printf("Number of frogs %d\n", frogs); 
	return 0; 
}
