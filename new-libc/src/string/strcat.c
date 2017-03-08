#include <gstddef.h>

#include <gstring.h>

char *gstrcat(char *s, const char *t)
{
	size_t len = gstrlen(s);
        gstrcpy(s+len, t);
        return s;
}

