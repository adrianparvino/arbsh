/*
Dangling pointers can be completely avoided in C by keeping an extra copy of
the original pointer. The idiom might be "a = b = malloc(..)" as opposed to
"a = malloc(..)". In this way we always have access to the original pointer
location and can free it without error.
*/


#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

int main(void)
{ 
	char *a;
	char *b;
	const char *string = "This is a string\n";

	a = b = malloc(32); // Always keep at least 2 copies of
			    // of the original pointer location.
	while (*string)
	{
		*b = *string;
		++string;
		++b; // "b" is now a dangling pointer
		     // and can not be freed
	}

	
	write(1, a, b - a); // when "b" is incremented away from "a" and
			    // becomes a dangling pointer then we can
			    // calculate the length of the object as b-a.

	free(a); // "a" however points at the original
		 // location that "b" pointed to and
		 // can be used to free the memory
	return 0; 
}

