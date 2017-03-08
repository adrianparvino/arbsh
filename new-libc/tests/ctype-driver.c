#include <gstdio.h>
#include <gctype.h>


int main()
{
	int i = 0;
	for ( ; i < 130 ; i++)
	{ 
		if (gisalnum(i))
			gprintf("isalnum\n"); 
		if (gisalpha(i))
			gprintf("isalpha\n"); 
		if (gisblank(i))
			gprintf("isblank\n"); 
		if (giscntrl(i))
			gprintf("iscntrl\n"); 
		if (gisdigit(i))
			gprintf("isdigit\n"); 
		if (gisgraph(i))
			gprintf("isgraph\n"); 
		if (gislower(i))
			gprintf("islower\n"); 
		if (gisprint(i))
			gprintf("isprint\n"); 
		if (gispunct(i))
			gprintf("ispunct\n"); 
		if (gisspace(i))
			gprintf("isspace\n"); 
		if (gisupper(i))
			gprintf("isupper\n"); 
		if (gisxdigit(i))
			gprintf("isxdigit\n"); 
		if (gisascii(i))
			gprintf("isascii\n"); 
		//gprintf("\n\n");
		//gprintf("gtolower %c\n", gtolower(i));
		//gprintf("gtoupper %c\n", gtoupper(i));

		//gprintf("%c --actual char\n", i); 
	}

	return 0;
}
