#include <curses.h> 

WINDOW *initscr(void)
{
	size_t len = 0;
	char buf[128];
	WINDOW *win = stdscr;

	if ( 1 )
		_vt100(); 

	if(!(_getdimension()))
		return NULL;

	noecho();

	win->x = COLS;
	win->y = LINES;

	len = sprintf(buf, "%s%s", ansiglb.t_eraseall, ansiglb.t_insertreset);
	write(win->fd, buf, len);
	move(1, 0);
	return win;
}

