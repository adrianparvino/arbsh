#include <gstdio.h>
#include <stdio.h>

/* working with i686, x86_64, powerpcle and to some extent mipsel */


int main(void)
{
	GFILE *fp;
	int status;
	char path[4096];

	if ((fp = gpopen("ls -la", "r")) == NULL)
		return 1;
	 
	while (gfgets(path, 4096, fp) != NULL) 
		gfprintf(gstdout, "%s", path);

	gpclose(fp);
	return 0;
}








