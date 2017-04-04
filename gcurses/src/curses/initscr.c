#include <gcurses/gcurses.h>

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
	move(1, 1);
	return win;
}
