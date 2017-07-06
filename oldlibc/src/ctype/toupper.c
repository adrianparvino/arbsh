#include <gctype.h>

int gtoupper(int x)
{
        if (gislower(x))
                return ('A' + x - 'a');
        else
                return x;
}

