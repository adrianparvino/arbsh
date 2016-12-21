#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <limits.h>
#include <stdint.h>
#include "ansicode.h"

int main(int argc, char *argv[])
{
	size_t i = 1;
	size_t j = 10;
	size_t k = 1;
	size_t l = 1;
	
	char string[1024];
	size_t len = SIZE_MAX ;
	//size_t len = SIZE_MAX; 
	//while (i< len)
	printf("%zu\n", (len % (len) / ( len / 10 )));
	printf("%zu %zu\n", UINTMAX_MAX , SIZE_MAX);
	return;
	while ( k < SIZE_MAX)
	{ 
		if ( k >= SIZE_MAX / 1000 )
		{
			l = 10;
			j = 1;
		}
		printf("%zu\n", (len % (i * j)) /( k / l));
		// string[len++] = convtab[(num % (i * 10)) / i ];
		//len = uintostr(string, i);
		//write(1, string, len);
		//write(1, "\n", 1);
	//	j /= 10;
		i *= 10;
		k *= 10;
		//i *= 10;
	} 
	printf("%zu %zu\n", UINTMAX_MAX , SIZE_MAX);
	return 0;
}
