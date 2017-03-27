#include <gstdio.h>

GFILE *gpopen(const char *command, const char *type)
{
	GFILE *ret;
	/* needs to call fork and execvp */
	return ret;
}

int gpcloe(GFILE *fp)
{
	int ret = 0;
	/* needs to call wait4 */
	gflose(fp);
	return ret;
}
