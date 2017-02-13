#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//#include "itoa.h"
#include "../stdio.h"

int main()
{
	char string[10] = { 'h', 'e', 'l', 'l', 'o' , '\0' };
	size_t zutest = 1234567;
	int dtest = -9879871; 
	char string1[1000] = { 0 };
	long ltest = 23459999;

	gprintf("gdprintf:\n");
	gdprintf(2, "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld\n", zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest); 
	gprintf("gprintf:\n");
	gprintf("%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld\n", zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest); 
	gprintf("gsprintf:\n");
	gsprintf(string1, "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld\n", zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest); 
	printf("%s", string1);

	printf("control:\n");
	printf("%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld\n", zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest); 

}

