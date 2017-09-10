#include <stdio.h>

int main(void)
{
	//int i = '!';
	int i = 0;
	printf("static int ascii[] = { ");
	while (i<='~')
	{
		if ( i % 8 == 0 )
			printf("\n");
		
		if ( i < '!')
			printf("' ', ");
		else
		printf("'%c', ", i );
		++i;
	}
	printf("};\n"); 
	return 0;
}
