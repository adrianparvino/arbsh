#include <stdio.h>
#include <gctype.h>


int main()
{
	int i = 0;
	for ( ; i < 127 ; i++)
	{ 
		if (gisalnum(i))
			printf("isalnum\n"); 
		if (gisalpha(i))
			printf("isalpha\n"); 
		if (gisblank(i))
			printf("isblank\n"); 
		if (giscntrl(i))
			printf("iscntrl\n"); 
		if (gisdigit(i))
			printf("isdigit\n"); 
		if (gisgraph(i))
			printf("isgraph\n"); 
		if (gislower(i))
			printf("islower\n"); 
		if (gisprint(i))
			printf("isprint\n"); 
		if (gispunct(i))
			printf("ispunct\n"); 
		if (gisspace(i))
			printf("isspace\n"); 
		if (gisupper(i))
			printf("isupper\n"); 
		if (gisxdigit(i))
			printf("isxdigit\n"); 
		if (gisascii(i))
			printf("isascii\n"); 
		//gprintf("\n\n");
		//gprintf("gtolower %c\n", gtolower(i));
		//gprintf("gtoupper %c\n", gtoupper(i));

		//gprintf("%c --actual char\n", i); 
	}

	return 0;
}
