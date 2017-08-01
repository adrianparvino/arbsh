#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

int main(void)
{ 
	char *a;
	char *b;

	a = b = malloc(32); // no need for sizeof with chars

	char *string = "This is a string\n";

	while (*string)
	{
		*b = *string;
		++string;
		++b; // "b" is now a dangling pointer
		     // and can not be freed
	}

	printf("%s", a);

	free(a); // "a" however points at the original
		 // location that "b" pointed to and
		 // can be used to free the memory
	return 0; 
}

