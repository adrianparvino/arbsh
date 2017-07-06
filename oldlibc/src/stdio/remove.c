#include <gstdio.h>
#include <gerrno.h>
#include <unistd.h>

int gremove(const char *file)
{
	if (unlink(file))
	{
		if (errno == EISDIR)
			return rmdir(file);
		return -1;
	}
	return 0;
}
