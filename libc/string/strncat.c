#include "../stddef/stddef.h"

#include "string.h"

char *gstrncat(char *s, const char *t, size_t lim)
{
	size_t len = strnlen(s, lim);
	lim -= len;
        strncpy(s+len, t, lim);
        return s;
}

