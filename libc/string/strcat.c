#include "../stddef/stddef.h"

#include "string.h"

char *gstrcat(char *s, const char *t)
{
	size_t len = gstrlen(s);
        gstrcpy(s+len, t);
        return s;
}

