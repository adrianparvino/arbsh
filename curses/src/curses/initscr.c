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
	win->len = (win->x * win->y);


	len = sprintf(buf, "%s%s", ansiglb.t_eraseall, ansiglb.t_insertreset);
	write(win->fd, buf, len);
	_setcursor(1, 1);
	wclrtobot(win);
	
	if (win->buf)
	{ 
		win->clearok = 1;
		_clear_ok_real(win); 
		free(win->buf);// yes this is cheap
		free(win->last);// yes this is cheap 
		win->buf = win->last = NULL;
		win->rp = win->buf;
	}
	
	return win;
}

