#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "itoa.h"
#include "stdio.h"

int main()
{
	char string[10] = { 'h', 'e', 'l', 'l', 'o' , '\0' };
	size_t zutest = 1234567;
	int dtest = -9879871; 
	char string1[1000] = { 0 };


	gprintf("%zu/%d/%s==%zu / %d / %s\n", zutest, dtest, string, zutest, dtest, string); 
	gsprintf(string1, "%zu/%d/%s==%zu / %d / %s\n", zutest, dtest, string, zutest, dtest, string); 
	printf("%s\n", string1);

}

