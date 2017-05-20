#include <curses.h>

int wrefresh(WINDOW *win)
{
	char buf[32];
	size_t len = 0;
	_setcursor(1, 0);
	//_setcursor(win->px, win->py);
	//clrtobot();
	//if (win->clearok == 1)
	//{
		len = sprintf(buf, "%s", ansiglb.t_eraseall);
		write(win->fd, buf, len);
	//}
	write(win->fd, win->buf, win->rp - win->buf);
	win->rp = win->buf;
	_setcursor(win->px, win->py);
	return 0;
}
