#include <gstdio.h>
#include <gerrno.h>

void gperror(const char *interject)
{
	const char *message = strerror(errno);

	if (interject)
		gfprintf(gstderr, "%s: %s\n", interject, message);
	else
		gfprintf(gstderr, "%s\n", message);
}


