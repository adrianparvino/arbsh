
#include "stddef/stddef.h"
#include "ctype/ctype.h"
#include "string/string.h"
#include "stdio/stdio.h"



#include "stdlib/stdlib.h"
//#include "curses/curses.h"
#include "math/math.h"

#include "arb_str_math/arb_str.h"
int main (int argc, char *argv[])
{
	char *some = gmalloc(100); 

	int c = 'EOF';

	giscntrl(c);
	
	gstrcpy(some, argv[0]); 
	
	size_t ret = gstrlen(some);
	
	gsprintf(some + ret, "  Metamophosis\n");

	gprintf("%s\n", some);

	char *temp = gstrdup("a poem and a mistake");

	gprintf("surely %s\n", temp);

	gfprintf(gstdout, "------ %s\n", temp);

	char *out = gmalloc (1000);
	mirror = gmalloc (1000);
	tmpmir = gmalloc (1000);
	//out = addition("123", "123", out);

	

	//gfprintf(gstdout, "%s\n", out);

	//out = multiply("-123", "-121323", out);
	//arb_str_verbosity = 1;
	out = arb_str_divide("-123123123", "-321", out);
	gfprintf(gstdout, "%s\n", out);
	
	return 0;
}
