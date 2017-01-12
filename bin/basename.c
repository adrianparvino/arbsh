#include <unistd.h>
#include <string.h>

#include "../lib/libgen.h"

/*
	Copyright 2017, C. Graff  "basename"

	TODO: rewrite ../lib/libgen.h to be POSIX conformant,
	      currently this program will choke on / and /home/name/
	      until that is changed.
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
		write(2, "Basename needs > 1 arg\n", 23);
		return 1;
	}

	if (argc > 1)
	{
		hold = ggnu_basename(argv[1]);
		i = len = strlen(hold);

		if (!hold || !len)
			return 1;

		if (argc > 2)
        	{
			strip = argv[2];
	
			k = j = strlen(strip);

			for (;hold[len - 1] == strip[j - 1] ; --len, --j)
				;

			if ( i - len == k && len > 0)
				i = len;
        	}
		
		hold[i] = '\n';
                write(1, hold, i + 1);
	}

	return 0;
}


