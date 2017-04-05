#include <gcurses/gcurses.h>

int clrtoeol(void)
{
	return wclrtoeol(stdscr);
}

