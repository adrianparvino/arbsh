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
	gprintf("%s\n", string);
	gprintf("you are %zu sweety \n", zutest);
	gprintf("%s\n", string);
	
	printf("test3 %d\n", dtest);
	gprintf("test4 %d\n", dtest);

	char string1[1000] = { 0 };
	gprintf("%s/%s\n", string, string);
	//gprintf("%d/%s== %d / %s\n", dtest, string, dtest, string);
	gprintf("%zu/%d/%s==%zu / %d / %s\n", zutest, dtest, string, zutest, dtest, string);
	//gsprintf("%s/%s\n", string, string);
	//printf("test 5 %s\n", string1);
	//double flttest = 789987;
	//fltostr(string, flttest);
	//printf("%s\n", string);
}

