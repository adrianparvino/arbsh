#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int main(void)
{
	FILE *stream = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;

	stream = fopen("README", "r");

	while ((read = getline(&line, &len, stream)) != -1)
	{
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}

	free(line);
	fclose(stream);
	return 0;
}
