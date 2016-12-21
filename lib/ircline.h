/*
	2015 (C) Copyright, gshline.c, CM Graff
*/


/* function prototypes */
static int readchar(void);
size_t gshline(char *, char *, size_t);
size_t gshgetch(char *);
void gshprint(char *, size_t, char *, size_t);
int gsh_history(char *, size_t);
void determinewin(void); 
struct winsize win;

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
	tcgetattr(0, &oterm);
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	read(0, str, 1);
	tcsetattr(0, TCSANOW, &oterm);
	return str[0];
}

size_t gshline(char *l, char *prompt, size_t promptlen)
{ 
	size_t len = 0;
	hglb.r = 1; 
	
	while ( hglb.r )
	{ 
		determinewin();
		gshprint(l, len, prompt, promptlen); 
       		len = gshgetch(l);
	}

	return len;
}

size_t gshgetch(char *l)
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
		//uparse(l);
		//return 0;
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

void gshprint(char *l, size_t len, char *prompt, size_t plen)
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

int gsh_history(char *l, size_t len)
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

void determinewin(void)
{
	//struct winsize w;
	ioctl(0, TIOCGWINSZ, &win);
	hglb.w = win.ws_col;
	hglb.h = win.ws_row;
}

