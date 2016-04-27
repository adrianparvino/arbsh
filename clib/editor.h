/*
        A very simple text editor, which supports nothing
	Tt's here for reference, nothing else
*/


/* function prototypes */ 
size_t gshline(char *, size_t, int);
size_t gshgetch(char *, size_t, int);
void gshprint(char *, size_t);
void determinewin(void); 


/* structures */
struct hglb {		/* globals	*/
	size_t t;	/* Total	*/
	size_t c;	/* Current	*/
	int r;		/* Runstate	*/
	size_t laro;	/* left arrow(s)*/ 
        size_t w;
        size_t h;
} hglb = { 0, 0, 0, 0, 0, 0};


struct hist {			/* history lines	*/
	char line[BUFSIZ];	/* lines		*/ 
	size_t len;		/* line length		*/
}*hist;

size_t gshline(char *l, size_t len, int fp)
{ 
	//size_t len = 0;
	hglb.r = 1; 
	
	
	while ( hglb.r )
	{
		determinewin(); 
		gshprint(l, len);
       		len = gshgetch(l, len, fp);
	}

	return len;
}

size_t gshgetch(char *l, size_t len, int fp)
{
        //static size_t len = 0;
	//static size_t ret = 0;
	size_t z = 0;
        int c; 
       
	c = supahfastgetch(); 
        
        switch (c) { 
	case K_ESCAPE:
		c = supahfastgetch();
		switch (c) {
		case '[':
                        c = supahfastgetch();
			switch (c) { 
			case 'A': /* arrow up */ 
				/* in the case of an editor this would shift the cursor up a line */
				break;
			case 'B': /* arrow down */ 
				break;
			case 'C': /* right arrow */ 
				if ( hglb.laro > 0 )
					--hglb.laro;
                                break;
			case 'D': /* left arrow */ 
				if ( hglb.laro < len )
					++hglb.laro; 
				break; 
			case 'H': /* Home */
				hglb.laro = len;
                                break;
			case '5': /* page up ( not used ) */ 
				c = supahfastgetch(); 
				break;
			case '6': /* page down ( not used ) */ 
				c = supahfastgetch();
				break;
			}
		}
		return len; 

	case '\t': 
	
		len += 7;
		if ( hglb.laro )
                {
                        z = (len - hglb.laro);
                        memmove(l + z + 1, l + z, hglb.laro);
                        l[z] = c;
                }
                else {
                        l[len] = c;
                }

                l[++len] = '\0';
		
		break;
	case K_CTRLEXX:
		lseek(fp, 0, SEEK_SET);
		write(fp, l, len);
		break;
	case K_BACKSPACE:
		if ( len == 0 ) 
			return len; 
		if ( hglb.laro ) 
		{
			z = (len - hglb.laro);
                        memmove(l + z - 1, l + z, hglb.laro);
		}

		l[--len] = '\0';

		return len; 
        default:
		if ( hglb.laro )
		{
			z = (len - hglb.laro);
			memmove(l + z + 1, l + z, hglb.laro);
			l[z] = c; 
		}
		else { 
			l[len] = c;
		}

		l[++len] = '\0';

                break;
        }
	return len;
}

void gshprint(char *l, size_t len)
{ 
	size_t i;
	size_t y;
	size_t z;

	system("clear");

        /* write the buffer out to screen */
	write(1, l, len);

        /* walk the cursor backward to the user's position */
        for (i=0, y = len; i < hglb.laro ; ++i, --y)
        { 
		if ( ( l[y - 1] == '\n' ) )
                { 
			write(1, T_CURSUP1ROW, T_CURSUP1ROW_SZ);
                        for ( z = 1; l[y - (z + 1)] != '\n' && y - z > 0  ; ++z)
			{ 
				write(1, T_CURS4D1COL, T_CURS4D1COL_SZ); 
			}
                } 
		else if ( ( l[y] == '\t' ) )
		{
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
			//write(1, T_CURS4D1COL, T_CURSBK1COL_SZ);
		}
		else
			write(1, T_CURSBK1COL, T_CURSBK1COL_SZ); 
        }
}

void determinewin(void)
{
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        hglb.w = w.ws_col;
        hglb.h = w.ws_row;
}

