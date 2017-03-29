#include <stdio.h>

int main(void)
{
	FILE *fp;
	int status;
	char path[4096];

	if (( fp = popen("ls -la", "r")) == NULL)
		return 1;

	while (fgets(path, 4096, fp) != NULL)
		printf("%s", path); 

	return status = pclose(fp);
}


