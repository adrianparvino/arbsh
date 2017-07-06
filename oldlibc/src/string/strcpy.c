#include <gstddef.h>

#include <gstring.h>

char *gstrcpy(char *s, const char *t)
{
        for(;(*s = *t) != '\0'; s++, t++)
                ;
        return s;
}

