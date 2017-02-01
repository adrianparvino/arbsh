#include "stddef/stddef.h"
#include "ctype/ctype.h"
#include "string/string.h"
int main (int argc, char *argv[])
{
	char string[1024] = { 0 };
	giscntrl(argc);
	
	gstrcpy(string, argv[0]);
	puts("hey");
	write(1, "hello\n", 6);
	return 0;
}
