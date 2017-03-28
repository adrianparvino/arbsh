#include <stdio.h>

int main(void)
{
	FILE *fp;
	int status;
	char path[4096];

	fp = popen("ls -la", "r");
	if (fp == NULL)
		;

	while (fgets(path, 4096, fp) != NULL)
		printf("%s", path); 

	status = pclose(fp);
}


