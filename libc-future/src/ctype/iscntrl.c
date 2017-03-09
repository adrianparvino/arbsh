#include <gctype.h>

int giscntrl(int x)
{
        if (x >= '\0' && x < ' ' )
                return 1;
        return 0;
}

