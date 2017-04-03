#include <gcurses/gcurses.h>

int getch()
{
	char s[1];
	s[0] = 0;
	read(0, s, 1);
	return s[0];
}
