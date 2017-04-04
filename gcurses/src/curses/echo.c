#include <gcurses/gcurses.h>

int echo(void)
{
	_termcatch(~(ICANON & ECHO), 0);
	return 0;
}



