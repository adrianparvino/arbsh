#include "../stddef/stddef.h"

#include "string.h"

char *gstrchr(const char *s, int c)
{
        for ( ; *s != c; s++)
                if (*s == '\0')
                        return 0;
        return (char *)s;
}

