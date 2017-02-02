
#include "stddef/stddef.h"
#include "ctype/ctype.h"
#include "string/string.h"
#include "stdio/stdio.h"
#include "stdlib/stdlib.h"
int main (int argc, char *argv[])
{
	char *some = NULL;
	some = gmalloc(100);
	char string[1024] = { 0 };
	giscntrl(argc);
	
	gstrcpy(string, argv[1]);
	//gbasename(string);
	
	size_t ret = gstrlen(string);
	//gsprintf(string + ret, "asdlkjasdkj\n");
	//printf("%s", string);
	return 0;
}
