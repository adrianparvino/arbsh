#include <gcurses/gcurses.h>

int wgetch(WINDOW *win)
{
	char str[1];
	/* curses only has one input stream */
	win = win; 
	read(0, str, 1);
	return str[0];
}
