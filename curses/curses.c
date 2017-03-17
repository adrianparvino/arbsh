/* 
	Copyright 2016-2017, CM Graff, hexen.h 
*/ 


#include <curses/gcurses.h>

/* globals */
int dothink = 0;
int hardadd = 0; /* this should be added as a 4th function arg */
//Dstruct ansiglb ansiglb = { 0, 0, 0, 0};
struct ansiglb ansiglb;

//struct ANSIWINDOW ANSIWINDOW[10] = {{ 0,0, GNULL, GNULL, { GNULL } , { 0 } , {GNULL}}};
struct ANSIWINDOW ANSIWINDOW[10];


/* functions */
int fastgetch() 
{ 
	char s[1]; 
	s[0] = 0; 
	read(0, s, 1); 
	return s[0]; 
}

int ansigetch(void)
{
	static struct termios term, oterm;
	char str[1];
	str[0] = 0;
	if ((tcgetattr(0, &oterm)) != 0)
		return -1;
	gmemcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO); 
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSANOW, &term)) != 0 )
		return -1;
	read(0, str, 1);
	if ((tcsetattr(0, TCSANOW, &oterm)) != 0 )
		return -1;
	return str[0];
} 

int termcatch(int flags, int reset)
{ 
	static int set = 0;
	static struct termios term, oterm;
	
	/* catch the user's original terminal state _once_ */
	if ( set == 0 )
	{
		if ((tcgetattr(0, &oterm)) != 0 )
			return -1;
		gmemcpy(&term, &oterm, sizeof(term));
		set = 1;
	}
	/* Set the programmer's terminal attributes */
	if ( reset == 0 )
	{
		term.c_lflag &= (flags);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;

		if ((tcsetattr(0, TCSANOW, &term)) == 0 )
			return 0;
	/* Programmer access to reset user's terminal state */
	}else if ( reset == 1 )
		if ((tcsetattr(0, TCSANOW, &oterm)) == 0 )
			return 0;

	return -1;
	
}

void setcursor(size_t x, size_t y)
{ 
	/* [24;80H	Pos to line 24 col 80 (any line 1 to 24, any col 1 to 132)*/
	/* \033[?;?H */
	char str[1025] = { 0 };
	size_t len = 0;
	len = gsprintf(str, "\033[%zu;%zuH", x, y);
	write(0, str, len);
}

void setcursorchars(size_t x, size_t y, char s)
{
	/* \033[?;?H? */
	char hold[2] = { 0 };
        hold[0] = s;
	char str[1025] = { 0 }; 
	size_t len = 0;
	len = gsprintf(str, "\033[%zu;%zuH%s", x, y, hold);
	write(0, str, len);
}

void ansihorizon(size_t x, size_t X)
{ 
	/* [20;40r	Scrolling region set to lines 20 -> 40  	*/
	/* \033[?;?r */
	char str[1025] = { 0 };
	size_t len = 0;
	len = gsprintf(str, "\033[%zu;%zur", x, X);
	write(0, str, len);
}

int ansiinit(void)
{
	int ret = 0;
	struct winsize w;

	if ( (ret = ioctl(0, TIOCGWINSZ, &w)) == -1)
		return ret;
	ansiglb.col = w.ws_col;
	ansiglb.row = w.ws_row;
	
	write(1, T_ERASEALL, T_ERASEALL_SZ);
	write(1,T_INSERTRESET, T_INSERTRESET_SZ);
	return ret;
}

void addcolor(char *string, size_t len, size_t position)
{ 
	/* only allow each color to be set away from white once */
	char *p = T_WHITE_FG;
	if (ANSIWINDOW[ansiglb.c].cpairs[position] != p && string != p && hardadd !=1)
		return;
	ANSIWINDOW[ansiglb.c].cpairs[position] = string;
	ANSIWINDOW[ansiglb.c].colordlen[position] = len;
}

void addcolorrange(char *string, size_t len, size_t position, size_t end)
{
        /* only allow each color to be set away from white once */
	char *p = T_WHITE_FG;
	while ( position < end )
	{
        
	        if (ANSIWINDOW[ansiglb.c].cpairs[position] != p && string != p && hardadd !=1)
	                return;
	        ANSIWINDOW[ansiglb.c].cpairs[position] = string;
	        ANSIWINDOW[ansiglb.c].colordlen[position] = len;
		++position;
	}
}

int ansicreate(void)
{
	size_t len = 0;
	len = ANSIWINDOW[ansiglb.t].len = ( ansiglb.col * ansiglb.row );
	ANSIWINDOW[ansiglb.t].ansilastmap = gmalloc(sizeof(char) * len * 10);
	ANSIWINDOW[ansiglb.t].ansiwinbuf = gmalloc(sizeof(char) * len * 10);
	gmemset(ANSIWINDOW[ansiglb.t].colorlast, 0, (len * 10));
	gmemset(ANSIWINDOW[ansiglb.t].ansilastmap, 0, (len * 10));
	ansiglb.c = ansiglb.t;
	size_t i = 0;
	while (i < (len))
		addcolor(T_WHITE_FG,T_WHITE_FG_SZ, i++);
	ansiglb.t++;
	return (ansiglb.t) - 1;
}

int ansidestroy(void)
{
	gfree(ANSIWINDOW[ansiglb.c].ansilastmap);
	gfree(ANSIWINDOW[ansiglb.c].ansiwinbuf);
	return 0;
}

int ansiwaddch(int ch, int position)
{
	/* ansiwaddch adds a char into the current cursor position on screen */ 
	ANSIWINDOW[ansiglb.c].ansiwinbuf[position] = ch;
	return 0;
} 

int ansiaddmem(char *str, int position, size_t end)
{
	/* ansiwaddmem adds a series of bytes to the current ANSIWINDOW[ */ 
	size_t i = position;
	size_t ret = 0;
	for( ret = 0;i < end ; ++i, ++ret) 
		ANSIWINDOW[ansiglb.c].ansiwinbuf[i] = str[ret]; 
	return ret;
}

size_t ansiaddstr(char *str, size_t position)
{
	/* add a string, discard the '\0' */
	size_t i = position;
	size_t ret = 0; 
	for( ret = 0;str[ret] != '\0' ; ++i, ++ret) 
		ANSIWINDOW[ansiglb.c].ansiwinbuf[i] = str[ret]; 
	return ret;
}

int ansiredraw(size_t lim, size_t x, size_t y, size_t rightmarg)
{ 
	/* print a fully populated ansiwinbuf */
	size_t i = 0;
	size_t j = 1 + y;
	size_t k = 1 + x;
	int a = 0;
	int b = 0;
	char *c;
	char *d;
	
	while ( i < lim ) 
	{
		a = ANSIWINDOW[ansiglb.c].ansiwinbuf[i];
		b = ANSIWINDOW[ansiglb.c].ansilastmap[i]; 
		c = ANSIWINDOW[ansiglb.c].cpairs[i];
		d = ANSIWINDOW[ansiglb.c].colorlast[i]; 
		
		if ( dothink || a != b || c != d) 
		{ 
			setcursor(k, j); 
			write(0, ANSIWINDOW[ansiglb.c].cpairs[i], ANSIWINDOW[ansiglb.c].colordlen[i]);
			ANSIWINDOW[ansiglb.c].colorlast[i] = c; 
			setcursorchars(k, j, ANSIWINDOW[ansiglb.c].ansiwinbuf[i]); 
			ANSIWINDOW[ansiglb.c].ansilastmap[i] = a; 
			addcolor(T_WHITE_FG,T_WHITE_FG_SZ, i);
		} 
		if ( j == ansiglb.col - rightmarg) 
		{
			j = 0 + y;
			++k;
		} 
		++i;
		++j; 
	}
	return 0;
}
