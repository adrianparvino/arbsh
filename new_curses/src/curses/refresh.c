#include <gcurses/gcurses.h>

int refresh(void)
{
	return wrefresh(stdscr);
}
