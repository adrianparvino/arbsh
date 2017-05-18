#include <curses/gcurses.h>

struct ansiglb ansiglb;
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
	if ( set == 0 )
	{
		if ((tcgetattr(0, &oterm)) != 0 )
			return -1;
		gmemcpy(&term, &oterm, sizeof(term));
		set = 1;
	} 
	if ( reset == 0 )
	{
		term.c_lflag &= (flags);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0; 
		if ((tcsetattr(0, TCSANOW, &term)) == 0 )
			return 0; 
	}else if ( reset == 1 )
		if ((tcsetattr(0, TCSANOW, &oterm)) == 0 )
			return 0; 
	return -1; 
}

void setcursor(size_t x, size_t y)
{ 
	char str[1025] = { 0 };
	size_t len = 0;
	len = gsprintf(str, "\033[%zu;%zuH", x, y);
	write(0, str, len);
}

void setcursorchars(size_t x, size_t y, char s)
{ 
	char hold[2] = { 0 };
        hold[0] = s;
	char str[1025] = { 0 }; 
	size_t len = 0;
	len = gsprintf(str, "\033[%zu;%zuH%s", x, y, hold);
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

int ansiredraw(size_t lim, size_t x, size_t y, size_t rightmarg)
{
	size_t i = 0;
	size_t j = 1 + y;
	size_t k = 1 + x;
	int a = 0;
	int b = 0;
	
	for( ;i < lim; ++i, ++j) 
	{
		a = ANSIWINDOW[ansiglb.c].ansiwinbuf[i];
		b = ANSIWINDOW[ansiglb.c].ansilastmap[i]; 
		if ( a != b) 
		{ 
			setcursorchars(k, j, ANSIWINDOW[ansiglb.c].ansiwinbuf[i]); 
			ANSIWINDOW[ansiglb.c].ansilastmap[i] = a; 
		}
		if ( j == ansiglb.col - rightmarg) 
		{
			j = 0 + y;
			++k;
		}
	}
	return 0;
}
int ansicreate(void)
{
	size_t len = 0;
	len = ANSIWINDOW[ansiglb.t].len = ( ansiglb.col * ansiglb.row );
	ANSIWINDOW[ansiglb.t].ansilastmap = gmalloc(sizeof(char) * len * 10);
	ANSIWINDOW[ansiglb.t].ansiwinbuf = gmalloc(sizeof(char) * len * 10); 
	gmemset(ANSIWINDOW[ansiglb.t].ansilastmap, 0, (len * 10));
	ansiglb.c = ansiglb.t;
	size_t i = 0; 
	ansiglb.t++;
	return (ansiglb.t) - 1;
}
