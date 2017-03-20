#include <gstddef.h>

#include <gstring.h>

void *gmemchr(const void *str, int c, size_t n)
{
	size_t i = 0;
	const char *s = str;

	for ( ; i < n; i++, s++)
		if (*s == c)
			return (char *)s;
	return NULL;
}

