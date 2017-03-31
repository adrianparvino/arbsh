#include <gerror.h>

char *gstrerror(int errnum)
{
	return _messages[errnum];
}
