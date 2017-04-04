#include <gcurses/gcurses.h>

WINDOW *initscr(void)
{
	int ret = 0;
	struct winsize w;
	size_t len = 0;
	char buf[128];
	WINDOW *win = stdscr;

	if ((ret = ioctl(0, TIOCGWINSZ, &w)) == -1)
		return NULL;
	ansiglb.col = w.ws_col;
	ansiglb.row = w.ws_row;
	ansiglb.t_eraseall = T_ERASEALL;
	ansiglb.t_insertreset = T_INSERTRESET;
	ansiglb.t_gohome = T_GOHOME;
	ansiglb.t_clrcur2bot = T_CLRCUR2BOT;
	len = sprintf(buf, "%s%s", ansiglb.t_eraseall, ansiglb.t_insertreset);
	write(1, buf, len);
	move(1, 1);
	return win;
}
