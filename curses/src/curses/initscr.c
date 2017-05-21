#include <curses.h>

// TODO: Load values into ansiglb at run time from terminfo 

int _getdimension(void)
{
	struct winsize w;
	int ret = 0;
	if ((ret = ioctl(0, TIOCGWINSZ, &w)) == -1)
                return 0;
	COLS = ansiglb.col = w.ws_col;
        LINES = ansiglb.row = w.ws_row;
	return 1;
}

void _vt100(void)
{
	ansiglb.t_insertreset = T_INSERTRESET;
	ansiglb.t_clrcur2bot = T_CLRCUR2BOT;
	ansiglb.t_clrtoeol = T_CLRCUR2END;
	ansiglb.t_eraseall = T_ERASEALL;
}

void _vt52(void)
{
	ansiglb.t_insertreset = T_INSERTRESET;
        ansiglb.t_clrcur2bot = T_CLRCUR2BOT;
        ansiglb.t_clrtoeol = T_CLRCUR2END;
        ansiglb.t_eraseall = T_ERASEALL;
}

WINDOW *initscr(void)
{ 
	struct winsize w;
	size_t len = 0;
	char buf[128];
	WINDOW *win = stdscr;

	/* populate the global structure */
	if ( 1 ) /* vt100 mode should be activated by an environment trigger */
		_vt100();

	/* populate stdscr */
	if(!(_getdimension()))
		return NULL;

	noecho();

	win->x = COLS;
	win->y = LINES;

	len = sprintf(buf, "%s%s", ansiglb.t_eraseall, ansiglb.t_insertreset);
	write(1, buf, len);
	move(1, 1);
	return win;
}

