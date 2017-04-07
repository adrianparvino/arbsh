#include <gstddef.h>
#include <gstring.h>


size_t gstrspn(const char *s1, const char *s2)
{
        size_t i = 0;
        size_t j = 0;

        for ( ; *(s1+i) ; i++)
        {
                for (j = 0 ; *(s2+j) ; j++)
                        if(*(s1+i) == *(s2+j))
                                break; /* Found a match. */
                if (!*(s2+j))
                        return i; /* No match found. */
        }
        return i;
}

