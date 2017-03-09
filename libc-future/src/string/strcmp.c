#include <gstddef.h>

#include <gstring.h>

int gstrcmp(char *s, char *t)
{
        for ( ; *s == *t; s++, t++)
                if (*s == '\0')
                        return 0;
        return *s - *t;
}
