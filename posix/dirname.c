#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>
#include "../lib/libgen.h"

/*
	Copyright 2017, C. Graff  "dirname"

	not yet implemented 

*/

int main(int argc, char *argv[]) 
{ 
	char *hold;
	char *hold2;
	char string[4096] = { 0 };
	if (argc < 2 )
	{
		write(2, "Dirname needs > 1 arg\n", 22);
		return 1;
	} 
	strcpy(string, argv[1]);
	hold = dirname(string);
	printf("%s\n", hold);

	
	hold2 = gdirname(argv[1]);
	printf("%s\n", hold2);
	return 0;
}


