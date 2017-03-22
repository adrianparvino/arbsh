#include <gstddef.h>


size_t __safe_increment(size_t i, size_t request, size_t limit)
{
	/*
		Usage:
		i = __safe_increment(i, request, SIZE_MAX);
	*/
	if ((limit - i) >= request )
		return i + request;
	return limit;
}

