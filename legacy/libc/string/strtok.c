#include "../stddef/stddef.h"

#include "string.h"

char *gstrtok(char *s, const char *delim)
{

        char *token;
        char *span;
        static char *last;

        int c;
        int hold;

        if (s == GNULL)
        {
                s = last;
                if (s == GNULL)
                        return GNULL;
        }


        c = *s++;

        for (span = (char *)delim; (hold = *span++) != 0;)
        {
                if (c == hold)
                {
                        c = *s++;
                        span = (char *)delim;
                }
        }

        if (c == 0)
                return (last = GNULL);

        token = s - 1;

        while ( 1 )
        {
                c = *s++;
                span = (char *)delim;
                do {
                        if ((hold = *span++) == c)
                        {
                                if (c == 0)
                                        s = GNULL;
                                else
                                        s[-1] = 0;
                                last = s;
                                return (token);
                        }
                } while (hold != 0);
        }
}

