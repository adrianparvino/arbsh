#include <stdio.h>
#include <unistd.h>
#include "itoa.h"
#include "stdio.h"

int main()
{
	char string[10] = { 'h', 'e', 'l', 'l', 'o' , '\0' };
	size_t zutest = 1234567;
	gprintf("%s\n", string);
	gprintf("you are %zu sweety \n", zutest);
	gprintf("%s\n", string);
}

