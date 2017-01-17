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
	char *hold = NULL;
	size_t len = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	char *strip = NULL;

	if (argc < 2 )
	{
		write(2, "Dirname needs > 1 arg\n", 22);
		return 1;
	}

	hold = gdirname(argv[1]);
	i = len = strlen(hold);

	if (!hold || !len)
		return 1;

	return 0;
}


