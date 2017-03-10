#include <gctype.h>

int gisprint(int x)
{
        if ( giscntrl(x))
                return 0;
        if ( x == ' ' )
                return 1;
        if (gisspace(x) == 0)
                return 1;
        return 0;
}

