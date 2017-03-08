#include <gstddef.h>

#include <gstring.h>

char *gstrchr(const char *s, int c)
{
        for ( ; *s != c; s++)
                if (*s == '\0')
                        return 0;
        return (char *)s;
}

