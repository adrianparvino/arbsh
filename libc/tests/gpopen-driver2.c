#include <gstdio.h>
#include <stdio.h>

int main(void)
{
	GFILE *fp;
	int status;
	char path[4096];
	int c = 0;

	if (( fp = gpopen("ls -la", "r")) == NULL)
		return 1;
	
	while ((c = gfgetc(fp)) != EOF)
		gfputc(c, gstdout);

	gpclose(fp);
	return 0;
}


