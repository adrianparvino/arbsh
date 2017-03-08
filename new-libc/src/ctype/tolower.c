#include <gctype.h>

int gtolower(int x)
{
        if (gisupper(x))
                return ('a' + x - 'A');
        else
                return x;
}
