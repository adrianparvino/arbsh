#include <gctype.h>

int gisxdigit(int x)
{
        if (gisdigit(x))
                return 1;
        if (x >= 'a' && x <= 'f')
                return 1;
        if (x >= 'A' && x <= 'F')
                return 1;
        return 0;
}


