#include <gstdio.h>
#include <gerrno.h>

void gperror(const char *interject)
{
	const char *message;
	const char *str = "";
	const char *delim = "";

	if ((message = strerror(errno)) == NULL)
		return;

	if (interject)
	{
		str = interject;
		delim = ": ";
	}
	gfprintf(gstderr, "%s%s%s\n", str, delim, message);
}


