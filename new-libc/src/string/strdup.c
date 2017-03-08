#include <gstddef.h>

#include <gstring.h>

#include <gmalloc.h>

char *gstrdup(const char *s)
{
        char *ret;
        size_t len = gstrlen(s) + 1;
        ret = gmalloc(len);
        gmemcpy(ret, s, len);
        return ret;
}


