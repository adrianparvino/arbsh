#include "ctype.h"

int gisblank(int x)
{
        int ret = 1;
        switch(x)
        {
                case ' ':
                        return ret;
                        break;
                case '\t':
                        return ret;
                        break;
                default:
                        ret = 0;
                        break;
        }
        return ret;
}

