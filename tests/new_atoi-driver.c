#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main()
{
	int a = atoi("-123123");
	printf("%d\n", a);

	a = atoi("-1231235");
	printf("%d\n", a);

	a = atoi("-12312323");
	printf("%d\n", a);

	a = atoi("+123123898");
	printf("%d\n", a);

	a = atoi("+1231239877");
	printf("%d\n", a);

	a = atoi("-123123898");
	printf("%d\n", a);

	a = atoi("-1231239877");
	printf("%d\n", a);

	a = atoi("-99999999999999999");
	printf("%d\n", a);

	a = atoi("-999999999999999999");
	printf("%d\n", a);
	
	a = atoi("+9999912399999999");
	printf("%d\n", a);
	
	a = atoi("      -11199999999");
	printf("%d\n", a);
	
	a = atoi("      +11199999999");
	printf("%d\n", a);

	
	a = atoi("-999999999999999999999");
	printf("%d\n", a);

	/* glibc truncates larger arguments
	a = atoi("999999999999999999");
	printf("%d\n", a);

	a = atoi("-999999999999999999999");
	printf("%d\n", a);

	a = atoi("-999999999999999999999");
	printf("%d\n", a);

	a = atoi("999999999999999999999");
	printf("%d\n", a);

	a = atoi("999999999999999999999");
	printf("%d\n", a);
	*/
}
