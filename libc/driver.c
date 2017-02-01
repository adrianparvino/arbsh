
#include "stddef/stddef.h"
#include "ctype/ctype.h"
#include "string/string.h"
int main (int argc, char *argv[])
{
	char string[1024] = { 0 };
	giscntrl(argc);
	
	gstrcpy(string, argv[0]);
	
	return 0;
}
