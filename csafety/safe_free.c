#include <stdio.h>

void safe_free(void *a)
{
	/*
		Check that memory is not NULL before freeing it.
		Note: This only works if all freed memory is explicitly set to
		NULL
	*/

	if (a)
		free(a)
	else {
		fprintf(stderr, "A double free was detected\n");
	}
	/* Explicitly force structure members to be NULL */
	a = NULL;

}


