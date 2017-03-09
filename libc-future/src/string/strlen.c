#include <gstddef.h> 
#include <gstring.h> 

size_t gstrlen(const char *s)
{
        size_t i = 0;
        while ( s[i] != '\0' )
                ++i;
        return i;
}


