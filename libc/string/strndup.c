#include "../stddef/stddef.h"

#include "string.h"

char *gstrndup(const char *s, size_t lim)
{
        char *ret;
        size_t len = gstrnlen(s, lim) + 1;
        ret = gmalloc(len);
        gmemcpy(ret, s, len);
        ret[len] = 0;
        return ret;
}

