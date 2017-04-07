#include <gcurses/gcurses.h>

int getch(void)
{ 
	return wgetch(stdscr);
}
