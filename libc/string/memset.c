#include "../stddef/stddef.h"

#include "string.h"

void* gmemset(void *s, int c, size_t len)
{
        unsigned char *dst = s;
        for (;len > 0; dst++,len--)
                *dst = (unsigned char) c;
        return s;
}

