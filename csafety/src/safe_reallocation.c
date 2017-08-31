/*
There are very few tricks that universally apply to all C memory management. By
using the idiom of passing the value of a pointer to a pointer to a type to a
wrapper for free, realloc and malloc however, one can force a number of useful
scenarios. One such scenario is to take advantage of the C standard's specified
behavior for realloc; "If memory for the new object cannot be allocated, the 
old object is not deallocated and its value is unchanged" in the C11 draft.
We can therefore reduce this operation to a single line of code using a wrapper
function. Similiarly, all free'd memory can be explicitly made to point to NULL
. Malloc in this case performs no special function but is wrapped in the same
way as free and realloc in order to present a consistent API.
*/

	#include <stdio.h>
	#include <stdlib.h>

	int safe_free(void **a)
	{
		if (*a == NULL)
		{
			fprintf(stderr, "Warning: NULL passed to free\n");
			return -1;
		}
		free(*a);
		*a = NULL;
		return 1;
	}

	int safe_realloc(void **a, size_t i)
	{
		void *tmp;
		if (!(tmp = realloc(*a, i)))
		{
			perror("Realloc error: ");
			return -1;
		}
		*a = tmp;
		return 1;
	}

	int safe_malloc(void **a, size_t i)
	{ 
	        if (!(*a = malloc(i)))
	        {
	                perror("Malloc error: ");
	                return -1;
	        }
		return 1;
	}

	int main(void)
	{
		char *a;
		if (!(safe_malloc((void**)&a, 1)))
			return 1;

		if (!(safe_realloc((void**)&a, 10)))
			return 1;

		if (a)
			printf("a  exists\n");
	
		if (!(safe_realloc((void**)&a, (size_t)-1))) // will fail
			;//return 1

		if (a)
	                printf("a  exists\n");

		if(!(safe_free((void**)&a)))
			;// NULL pointers passed to free indicate design flaw

		return 0;
	}

