#include <stdio.h>
#include <stdio.h>


int main(void)
{
	FILE *fp;
	int status;
	char path[4096];


	fp = popen("ls -la", "r");
	if (fp == NULL)
		;


	//while (fgets(path, 4096, fp) != NULL)
	//	printf("%s", path);

	//write(1, "Was here\n", 9);
	//status = pclose(fp);
}








