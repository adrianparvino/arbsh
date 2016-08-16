#include <unistd.h>

int main(int argc, char **argv)
{
	/* Usage: ./simple_execute ls -la */
	if (argc > 1) 
		execvp(*(argv + 1), (argv + 1));
	
	return 0;
}

