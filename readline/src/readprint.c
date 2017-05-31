#include <readline/readline.h>

void greadprint(char *l, size_t len, char *prompt, size_t plen)
{ 
	
        static size_t deep = 0;
	size_t i;
	size_t j;
	size_t y;
	size_t z;
        
	/* calculate row pos and shove lines up */
        for (i = plen, j = len; j > (hglb.w - i) + 1; i = 0)
        { 
		if ( deep == 0 ) /* if user is scanning don't shove lines */
                	write(1, T_CURSUP1ROW, T_CURSUP1ROW_SZ);
		else if ( deep > 0 )
			--deep;
		j -= ( hglb.w - i);
        }
   
	/* clear character attributes */
	write(1, T_CLRCHARS, T_CLRCHARS_SZ);

        /* clear the line */
        write(1, "\r", 1);

        /* write the prompt out */
        write(1, prompt, plen);

        /* write the user's line out */
        write(1, l, len);

        /* clear to the end of the line ( ' ' .. + '\b' .. works too) */
        write(1, T_CLRCUR2END, T_CLRCUR2END_SZ);

        /* walk the cursor backward to the user's position */
        for (i=0, y = len + plen; i < hglb.laro ; ++i, --y)
        { 
               	write(1, T_CURSBK1COL, T_CURSBK1COL_SZ);
		if ( y % (hglb.w) == 0 )
		{
			write(1, T_CURSUP1ROW, T_CURSUP1ROW_SZ);
			for ( z=0; z < hglb.w ; ++z)
				write(1, T_CURS4D1COL, T_CURS4D1COL_SZ);
			++deep; 
		}
        }
}
