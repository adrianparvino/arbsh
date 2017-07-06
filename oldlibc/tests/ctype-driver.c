#include <stdio.h>
#include <ctype.h>


int main()
{
	int i = 0;
	for ( ; i < 127 ; i++)
	{ 
		if (isalnum(i))
			printf("isalnum\n"); 
		if (isalpha(i))
			printf("isalpha\n"); 
		if (isblank(i))
			printf("isblank\n"); 
		if (iscntrl(i))
			printf("iscntrl\n"); 
		if (isdigit(i))
			printf("isdigit\n"); 
		if (isgraph(i))
			printf("isgraph\n"); 
		if (islower(i))
			printf("islower\n"); 
		if (isprint(i))
			printf("isprint\n"); 
		if (ispunct(i))
			printf("ispunct\n"); 
		if (isspace(i))
			printf("isspace\n"); 
		if (isupper(i))
			printf("isupper\n"); 
		if (isxdigit(i))
			printf("isxdigit\n"); 
		if (isascii(i))
			printf("isascii\n"); 
		//printf("\n\n");
		//printf("tolower %c\n", tolower(i));
		//printf("toupper %c\n", toupper(i));

		//printf("%c --actual char\n", i); 
	}

	return 0;
}
