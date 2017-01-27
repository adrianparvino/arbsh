#include <stdio.h>
#include <ctype.h>
#include "ctype.h"

int main()
{
	size_t i = 0;
	for ( ; i < 127 ; i++)
	{
		int gisalnum(int);
		
		if (gisalnum(i))
			printf("gisalnum\n");
		if (isalnum(i))
			printf("isalnum\n");
		if (gisalpha(i))
			printf("gisalpha\n");
		if (isalpha(i))
			printf("isalpha\n"); 
		if (gisblank(i))
			printf("gisblank\n"); 
		if (isblank(i))
			printf("isblank\n");
		if (giscntrl(i))
			printf("giscntrl\n"); 
		if (iscntrl(i))
			printf("iscntrl\n"); 
		if (gisdigit(i))
			printf("gisdigit\n");
		if (isdigit(i))
			printf("isdigit\n");
		if (gisgraph(i))
			printf("gisgraph\n");
		if (isgraph(i))
			printf("isgraph\n");
		if (gislower(i))
			printf("gislower\n");
		if (islower(i))
			printf("islower\n");
		if (gisprint(i))
			printf("gisprint\n");
		if (isprint(i))
			printf("isprint\n");
		if (gispunct(i))
			printf("gispunct\n");
		if (ispunct(i))
			printf("ispunct\n");
		if (gisspace(i))
			printf("gisspace\n");
		if (isspace(i))
			printf("isspace\n");
		if (gisupper(i))
			printf("gisupper\n");
		if (isupper(i))
			printf("isupper\n");
		if (gisxdigit(i))
			printf("gisxdigit\n");
		if (isxdigit(i))
			printf("isxdigit\n");
		printf("\n\n");
			
		//printf("gtolower %c\n", gtolower(i));
		//printf("tolower %c\n", tolower(i));
	
		//printf("gtoupper %c\n", gtoupper(i));
		//printf("toupper %c\n", toupper(i)); 
	}

	return 0;
}
