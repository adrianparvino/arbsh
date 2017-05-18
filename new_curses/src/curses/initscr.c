#include <gcurses/gcurses.h>

// TODO: Load values into ansiglb at run time from terminfo 

WINDOW *initscr(void)
{
	int ret = 0;
	struct winsize w;
	size_t len = 0;
	char buf[128];
	WINDOW *win = stdscr;

	if ((ret = ioctl(0, TIOCGWINSZ, &w)) == -1)
		return NULL;

	/* populate the global structure */
	ansiglb.col = w.ws_col;
	ansiglb.row = w.ws_row;

	ansiglb.t_eraseall = T_ERASEALL;
	ansiglb.t_insertreset = T_INSERTRESET;
	ansiglb.t_gohome = T_GOHOME;
	ansiglb.t_clrcur2bot = T_CLRCUR2BOT;
	ansiglb.t_clrtoeol = T_CLRCUR2END;
	ansiglb.t_eraseall = T_ERASEALL;

	/* populate stdscr */
	win->x = ansiglb.col;
	win->y = ansiglb.row;

	len = sprintf(buf, "%s%s", ansiglb.t_eraseall, ansiglb.t_insertreset);
	write(1, buf, len);
	move(1, 1);
	return win;
}

