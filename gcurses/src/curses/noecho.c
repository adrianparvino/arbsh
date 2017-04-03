#include <gcurses/gcurses.h>

int noecho(void)
{
	_termcatch(~(ICANON | ECHO), 0);
	return 0;
}



