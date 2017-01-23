#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "stdio.h"
	

int main(void)
{
	GFILE *stream = GNULL;
	char *line = GNULL;
	size_t len = 0;
	ssize_t read = 0;

	stream = gfopen("README", "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);

	while ((read = ggetline(&line, &len, stream)) != -1)
	{
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}

	free(line);
	gfclose(stream);
	exit(EXIT_SUCCESS);
}
