
#include "../libc/stddef/stddef.h"
#include "../libc/ctype/ctype.h"
#include "../libc/string/string.h"
#include "../libc/stdio/stdio.h"



#include "../libc/stdlib/stdlib.h"
//#include "curses/curses.h"
#include "../libc/math/math.h"

#include "../libc/arb_str_math/arb_str.h"
int main (int argc, char *argv[])
{
	char *some = gmalloc(100); 

	

	giscntrl(3);
	
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
