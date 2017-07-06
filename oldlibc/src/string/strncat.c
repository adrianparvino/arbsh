#include <gstddef.h>

#include <gstring.h>

char *gstrncat(char *s, const char *t, size_t lim)
{
	size_t len = gstrnlen(s, lim);
	lim -= len;
        gstrncpy(s+len, t, lim);
        return s;
}

