#include "ctype.h"

int gisdigit(int x)
{
        if ( x >= '0' && x <= '9')
                return 1;
        return 0;
}

