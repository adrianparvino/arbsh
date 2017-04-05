#include <gcurses/gcurses.h>

int clearok(WINDOW *win, bool bf)
{
	win->clearok = bf;
	return 1;
}
