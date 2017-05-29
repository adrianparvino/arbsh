#include <gstdio.h>
#include <stdio.h>

int main(void)
{
	GFILE *fp;
	int status;
	char path[4096];

	if (( fp = gpopen("ls -la", "r")) == NULL)
		return 1;

	//while (fgets(path, 4096, fp) != NULL)
	//	printf("%s", path); 
	int c = 0;
	while ((c = gfgetc(fp)) != EOF)
		gfputc(c, gstdout);

	return status = gpclose(fp);
}


