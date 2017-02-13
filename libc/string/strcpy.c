#include "../stddef/stddef.h"

#include "string.h"

char *gstrcpy(char *s, const char *t)
{
        for(;(*s = *t) != '\0'; s++, t++)
                ;
        return s;
}

