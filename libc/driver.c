
#include "stddef/stddef.h"
#include "ctype/ctype.h"
#include "string/string.h"
#include "stdio/stdio.h"
#include "stdlib/stdlib.h"
#include "arbitrary/stringmath.h"
//#include "curses/curses.h"
#include "math/math.h"
int main (int argc, char *argv[])
{
	char *some = gmalloc(100); 

	int c = 'EOF';

	giscntrl(c);
	
	gstrcpy(some, argv[0]); 
	
	size_t ret = gstrlen(some);
	
	gsprintf(some + ret, "asdlkjasdkj\n");

	gprintf("%s\n", some);

	char *dogs = gstrdup("boooon");

	gprintf("hurm %s\n", dogs);

	gfprintf(gstdout, "hurm %s\n", dogs);

	char *out = gmalloc (1000);

	//out = addition("123", "123", out);

	

	//gfprintf(gstdout, "%s\n", out);

	out = multiply("-123", "-121323", out);

	gfprintf(gstdout, "%s\n", out);
	
	return 0;
}
