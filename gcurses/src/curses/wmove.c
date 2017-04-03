#include <gcurses/gcurses.h>

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
