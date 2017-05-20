#include <curses.h>

int wrefresh(WINDOW *win)
{
	char buf[32];
	size_t len = 0;
	if (win->clearok == 1)
	{
		len = sprintf(buf, "%s", ansiglb.t_eraseall);
		write(win->fd, buf, len);
	}
	write(win->fd, win->buf, win->rp - win->buf);
	return 0;
}
