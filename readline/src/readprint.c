#include <readline/readline.h>

size_t szstrcatn(char *dest, char *src, size_t limit, size_t offlen)
{
	/*
		Type of function that concatenates two strings
		and returns the number of bytes processed. The final
		argument "offlen" ensures that if a pointer offset
		is used with the first string that it will still not
		overflow.
	*/
	size_t destlen = strlen(dest);
	size_t i = 0;

	if ( offlen >= limit )
		return 0;

	for (i=0;destlen < (limit - offlen) - 1 && src[i] != 0;++i,++destlen) 
		dest[destlen] = src[i];
	
	dest[destlen] = 0;

	return destlen;
}

void greadprint(char *l, size_t len, char *prompt, size_t plen)
{
        static size_t deep = 0;
	size_t i;
	size_t j;
	size_t y;
	size_t z;
	char s[4096];
	size_t a = 0;
	size_t limit = 4095;
        
	s[0] = 0;
	
	/* calculate row pos and shove lines up */
        for (i = plen, j = len; j > (hglb.w - i) + 1; i = 0)
        { 
		if ( deep == 0 ) /* if user is scanning don't shove lines */
			a += szstrcatn(s + a, T_CURSUP1ROW, 4095, a);
		else if ( deep > 0 )
			--deep;
		j -= ( hglb.w - i);
        }
   
	/* clear character attributes */
	a += szstrcatn(s + a, T_CLRCHARS, 4095, a);

        /* clear the line */
	a += szstrcatn(s + a, "\r", 4095, a);

        /* write the prompt out */
	a += szstrcatn(s + a, prompt, 4095, a);

        /* write the user's line out */
	l[len] = 0;
	a += szstrcatn(s + a, l, 4095, a);

        /* clear to the end of the line ( ' ' .. + '\b' .. works too) */
	a += szstrcatn(s + a, T_CLRCUR2END, 4095, a);

        /* walk the cursor backward to the user's position */
        for (i=0, y = len + plen; i < hglb.laro ; ++i, --y)
        { 
		a += szstrcatn(s + a, T_CURSBK1COL, 4095, a);
		if ( y % (hglb.w) == 0 )
		{ 
			a += szstrcatn(s + a, T_CURSUP1ROW, 4095, a);
			for ( z=0; z < hglb.w ; ++z)
				a += szstrcatn(s + a, T_CURS4D1COL, 4095, a);
			++deep; 
		}
        }
	write(1, s, a);
}
