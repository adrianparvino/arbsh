#include <math.h>
#include <string.h> 
#include <stdio.h>
#include "../libc/string/strcpy.c"
//#include "../libc/stdio/stdio.h"
#include "../libc/stdio/dtoa.c"


int main(void)
{

	int i;
	char s[10];
	double d[] = {
		0.0,
		42.0,
		1234567.89012345,
		0.000000000000018,
		555555.55555555555555555,
		-888888888888888.8888888,
		111111111111111111111111.2222222222
	};
	for (i = 0; i < 7; i++) {
		printf("%d: printf: %.14g, dtoa: %s\n", i+1, d[i], gdtoa(s, d[i]));
	}
}

