#include <gerrno.h>
#include <gstring.h>

char *gstrerror(int errnum)
{
	return _messages[errnum];
}
