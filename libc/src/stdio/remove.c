#include <stdio.h>
#include <errno.h>

int gremove(const char *file) {
	if (unlink(file)) {
		if (errno == EISDIR)
			return rmdir(file);
		return -1;
	}
	return 0
}