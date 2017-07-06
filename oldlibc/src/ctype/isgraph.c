#include <gctype.h>

int gisgraph(int x)
{
        if (x == ' ')
                return 0;
        if (gisprint(x))
                return 1;
        return 0;
}

