#include <gstring.h>

int gstrcmp(const char *s, const char *t)
{
        for ( ; *s == *t; s++, t++)
                if (*s == '\0')
                        return 0;
        return *s - *t;
}
