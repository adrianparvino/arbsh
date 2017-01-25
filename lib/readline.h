/*
	2017 (C) Copyright, readline.h, CM Graff
*/

/* function prototypes */ 
size_t ircline(char *, char *, size_t);
void ircprint(char *, size_t, char *, size_t); 
void determinewin(void); 
static int readchar(void);
size_t greadline(char *, char *, size_t);
size_t greadgetch(char *);
void greadprint(char *, size_t, char *, size_t);
int gread_history(char *, size_t);

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

/* functions */
static int readchar(void)
{
	static struct termios term, oterm;
	char str[1];
	str[0] = 0;
	if ((tcgetattr(0, &oterm)) != 0)
		return -1;
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO); 
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSANOW, &term)) != 0 )
		return -1;
	read(0, str, 1);
	if ((tcsetattr(0, TCSANOW, &oterm)) != 0 )
		return -1;
	return str[0];
}

size_t ircline(char *l, char *prompt, size_t promptlen)
{ 
	size_t len = 0;
	hglb.r = 1; 
	
	while ( hglb.r )
	{ 
		determinewin();
		ircprint(l, len, prompt, promptlen);
		len = greadgetch(l);
	}

	return len;
}

void ircprint(char *l, size_t len, char *prompt, size_t plen)
{ 
	size_t i; 
	size_t real = 0; 
	size_t off = 0;
	size_t half;

	if ( len )
	{
		hglb.w = (hglb.w - 1 - plen);

		half = (hglb.w / 2);
	
		if ( len > (hglb.w) )
			off = len - hglb.w;
	}
	/* clear character attributes */
	write(1, T_CLRCHARS, T_CLRCHARS_SZ);
	
	/* clear the line */
	write(1, "\r", 1);
	write(1, T_CLRCUR2END, T_CLRCUR2END_SZ);

	/* write the prompt out */
	write(1, prompt, plen);
	
	if ( len )
	{
		if (hglb.laro >= half) 
			real = (hglb.laro - half); 

		/* write the user's line out */
		if (len < hglb.w)
	       	 	write(1, l, len);
		else if ( len - hglb.laro <= half ) 
			write(1, l, hglb.w);
		else
			write(1, l + off - real, hglb.w);

		if (hglb.laro)
		{
			/* split */
			if (len - hglb.laro > half )
			{
				for (i=0; i < hglb.laro && i < half; ++i) 
			       		write(1, T_CURSBK1COL, T_CURSBK1COL_SZ);
			}
			/* don't split */
			else if ( len < hglb.w )
			{
				for (i = 0; i < hglb.laro; ++i)
					write(1, T_CURSBK1COL, T_CURSBK1COL_SZ);
			}
			else
			{
				for (i = len - hglb.laro ; i < hglb.w; ++i) 
	      				write(1, T_CURSBK1COL, T_CURSBK1COL_SZ);
			} 
		}
	}
} 

void determinewin(void)
{ 
	struct winsize win;
	ioctl(0, TIOCGWINSZ, &win);
	hglb.w = win.ws_col;
	hglb.h = win.ws_row;
}

size_t greadline(char *l, char *prompt, size_t promptlen)
{ 
	size_t len = 0;
	hglb.r = 1; 
	
	while ( hglb.r )
	{
		determinewin(); 
		greadprint(l, len, prompt, promptlen); 
       		len = greadgetch(l);
	}

	return len;
}

size_t greadgetch(char *l)
{
        static size_t len = 0;
	static size_t ret = 0;
	size_t z = 0;
        int c; 
       
	c = readchar(); 
        
        switch (c) { 
	case K_ESCAPE:
		c = readchar();
		switch (c) {
		case '[':
                        c = readchar();
			switch (c) { 
			case 'A': /* arrow up */
				if ( hglb.c > 0 )
				{
					--hglb.c;
					strcpy(l, hist[hglb.c].line);
					len = hist[hglb.c].len;
					hglb.laro = 0;
				}
				break;
			case 'B': /* arrow down */
				if ( hglb.c < hglb.t )
				{
					++hglb.c;
					strcpy(l, hist[hglb.c].line);
					len = hist[hglb.c].len;
					hglb.laro = 0;
				}
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
				c = readchar(); 
				break;
			case '6': /* page down ( not used ) */ 
				c = readchar();
				break;
			}
		}
		return len;
	case '\t':
		//write(1, "tab complete\n", 13);
		break;
        case '\n':
		write(1, "\n", 1);
		l[len] = '\0';
		ret = len;
		len = 0;
		hglb.r = 0;
		hglb.laro = 0;
                return ret;
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

int gread_history(char *l, size_t len)
{
	if ( len > 1)
        { 
		if (!(hist = realloc(hist, sizeof(struct hist) * ( hglb.t + 1))))
                	return 0; // This _must_ be changed to a fatal error 
        	strcpy(hist[hglb.t].line, l);
		hist[hglb.t].len = len;
        	++hglb.t;
        }
	hglb.c = hglb.t;
	return 1;
}
