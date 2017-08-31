#include <stdio.h>
#include <stdlib.h>

int safe_realloc(void **a, size_t i)
{
	void *tmp;
	if (!(tmp = realloc(*a, i)))
	{
		perror("Realloc error: ");
		return 1;
	}
	*a = tmp;
	return 0;
}

int main(void)
{
	char *a;
	a = malloc(1);
	if ((safe_realloc((void**)&a, 10)))
		return 1;

	if (a)
		printf("a  exists\n");
	
	if ((safe_realloc((void**)&a, (size_t)-1))) // will fail
		;//return 1

	if (a)
                printf("a  exists\n");

	a = safe_free(a);

	return 0;
}

