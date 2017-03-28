#include <gstdio.h>



int main(void)
{
	GFILE *fp;
	int status;
	char path[4096];


	fp = gpopen("ls -la", "r");
	if (fp == NULL)
		;


	while (gfgets(path, 4096, fp) != NULL)
		gprintf("%s", path);


//	status = pclose(fp);
}








