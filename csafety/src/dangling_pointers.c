/*
Dangling pointers can be completely avoided in C by keeping an extra copy of
the original pointer. The idiom might be "a = b = malloc(..)" as opposed to
"a = malloc(..)". In this way we always have access to the original pointer
location and can free it without error. Presented below is a short program that
creates a dangling pointer but then uses a copy to the original pointer it had
saved to free it.
*/


#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

int main(void)
{ 
	char *a, *b;
	char *string = "This is a string\n";
	
	if (!(a = b = malloc(32))) /* keep an extra copy */
		return 1;
	while (*string)
		*b++ = *string++; /* "b" is now a dangling pointer */
	write(1, a, b - a); 
			    
	free(a); /* However, "a" can still be freed */
	return 0;           
}

