#include "ctype.h" 

int gisascii(int x)
{
        if (x >= 0 && x <= 127)
                return 1;
        else
                return 0;
}

