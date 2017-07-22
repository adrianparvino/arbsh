#include <curses.h>

void _setcursor(size_t x, size_t y)
{
	// x = LINES
	// y = COLS
        char str[1024] = { 0 };
        size_t len = 0;
	//y = y + 1;/* count y from 1 */
	//x +=1;
        len = sprintf(str, "\033[%zu;%zuH", x, y);
        write(1, str, len);
}

