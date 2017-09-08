#include <stdio.h>

int main(void)
{
	//int i = '!';
	int i = 0;
	printf(" = { ");
	while (i<='~')
	{
		if ( i % 8 == 0 )
			printf("\n");
		
		if ( i < '!')
			printf("'0', ");
		else
		printf("'%c', ", i );
		++i;
	}
	printf("};\n");

	i = 0;
	int j = 0;
	printf(" = { ");
	while (i<='~' + 100)
	{
		if ( i % 8 == 0 )
			printf("\n");
		
		if ( i < 'a')
			printf("000, ");
		else
			printf("%.3o, ", j++ );
		++i;
	}
	printf("};\n");
	return 0;
}
