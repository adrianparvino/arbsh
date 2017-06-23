#include <readline/readline.h>

void greadprint(char *l, size_t len, char *prompt, size_t plen)
{
        static size_t deep = 0;
	size_t i;
	size_t j;
	size_t y;
	size_t z;
	char s[4096];
	size_t a = 0;
        
	/* calculate row pos and shove lines up */
        for (i = plen, j = len; j > (hglb.w - i) + 1; i = 0)
        { 
		if ( deep == 0 ) /* if user is scanning don't shove lines */
			a += sprintf(s + a, "%s", T_CURSUP1ROW);
		else if ( deep > 0 )
			--deep;
		j -= ( hglb.w - i);
        }
   
	/* clear character attributes */
	a += sprintf(s + a, "%s", T_CLRCHARS); 

        /* clear the line */
	a += sprintf(s + a, "%s", "\r"); 

        /* write the prompt out */
	a += sprintf(s + a, "%s", prompt); 

        /* write the user's line out */
	l[len] = 0;
	a += sprintf(s + a, "%s", l); 

        /* clear to the end of the line ( ' ' .. + '\b' .. works too) */
	a += sprintf(s + a, "%s", T_CLRCUR2END); 

        /* walk the cursor backward to the user's position */
        for (i=0, y = len + plen; i < hglb.laro ; ++i, --y)
        { 
		a += sprintf(s + a, "%s", T_CURSBK1COL); 
		if ( y % (hglb.w) == 0 )
		{ 
			a += sprintf(s + a, "%s", T_CURSUP1ROW);
			for ( z=0; z < hglb.w ; ++z)
				a += sprintf(s + a, "%s", T_CURS4D1COL_SZ);
				//write(1, T_CURS4D1COL, T_CURS4D1COL_SZ);
			++deep; 
		}
        }
	write(1, s, a);
}
