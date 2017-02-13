#include "../stddef/stddef.h"

#include "string.h"

char *gstrcat(char *s, const char *t)
{
	size_t len = strlen(s);
        strcpy(s+len, t);
        return s;
}

