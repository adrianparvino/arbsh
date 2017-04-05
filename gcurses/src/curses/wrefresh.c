#include <gcurses/gcurses.h>

int wrefresh(WINDOW *win)
{
	if ( win->clearok == 1)
		;// 
	win = win;// draw
	return 0;
}
