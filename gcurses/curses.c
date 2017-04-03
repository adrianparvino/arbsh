#include <gcurses/gcurses.h>

struct ansiglb ansiglb;

/* functions */
int getch()
{
	char s[1];
	s[0] = 0;
	read(0, s, 1);
	return s[0];
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
		memcpy(&term, &oterm, sizeof(term));
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

int wmove(WINDOW *win, size_t x, size_t y)
{
	/* [24;80H	Pos to line 24 col 80 (any line 1 to 24, any col 1 to 132)*/
	/* \033[?;?H */
	char str[1025] = { 0 };
	size_t len = 0;
	len = sprintf(str, "\033[%zu;%zuH", x, y);
	write(win->fd, str, len);
	return 1;
}

int move (size_t x, size_t y)
{ 
	return wmove(stdscr, x, y);
}

void setcursorchars(size_t x, size_t y, char s)
{
	/* \033[?;?H? */
	char hold[2] = { 0 };
        hold[0] = s;
	char str[1025] = { 0 }; 
	size_t len = 0;
	len = sprintf(str, "\033[%zu;%zuH%s", x, y, hold);
	write(0, str, len);
}

WINDOW *initscr(void)
{
	int ret = 0;
	struct winsize w;
	WINDOW *win = NULL;

	if ((ret = ioctl(0, TIOCGWINSZ, &w)) == -1)
		return NULL;
	ansiglb.col = w.ws_col;
	ansiglb.row = w.ws_row;

	write(1, T_ERASEALL, T_ERASEALL_SZ);
	write(1,T_INSERTRESET, T_INSERTRESET_SZ);
	return win;
}

int addch(const char);
int waddch(WINDOW *win, const char ch);
int mvaddch(int y, int x, const char ch);
int mvwaddch(WINDOW *win, int y, int x, const char ch);
int echochar(const char ch);
int wechochar(WINDOW *win, const char ch); 


