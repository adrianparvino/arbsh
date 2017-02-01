#include "../stddef/stddef.h" 
#include "string.h"

size_t gstrnlen(const char *s, size_t lim)
{
        size_t i = 0;
        while ( s[i] != '\0' && i < lim)
                ++i;
        return i;
}

