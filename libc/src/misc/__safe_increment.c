#include <gstddef.h>
#include <gstdlib.h>
#include <gstddef.h>
#include <gstring.h>
#include <glimits.h>


#include <libc_impl.h>

size_t _safe_add(size_t i, size_t request, size_t limit)
{
	if ((limit - i) >= request )
		return i + request;
	return limit;
}

size_t _safe_mul(size_t i, size_t request, size_t limit)
{
	if ((limit / request) <= i)
		return i * request; 
	return limit;
}

