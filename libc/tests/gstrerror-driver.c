#include <gstring.h>
#include <unistd.h>
#include <gerrno.h>

int main(void)
{
	char *message = gstrerror(EPERM);
	size_t len =gstrlen(message);
	write(1, message, len);
	return 0;
}
