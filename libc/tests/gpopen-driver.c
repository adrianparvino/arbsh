#include <gstdio.h>
#include <stdio.h>



int main(void)
{
	GFILE *fp;
	int status;
	char path[4096];

	if ((fp = gpopen("ls -la", "r")) == NULL)
		return 1;
	 
	while (gfgets(path, 4096, fp) != NULL) 
		gprintf("%s", path); 

	return status = gpclose(fp);
}








