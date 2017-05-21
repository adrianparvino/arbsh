#include <curses.h>

int waddch(WINDOW *win, chtype ch)
{
	
	if (win->buf == NULL)
	{
		win->len = (win->x * win->y);
		if ((win->buf = malloc(sizeof(char) * win->len)) == NULL)
		{ 
			win->len = 0;
			return -1;
		}
		win->rp = win->buf;
	}
	if (win->len > 0)
		win->len--;

	
	if (win->len == 0)
	{
		wrefresh(win);
		win->rp = win->buf;
		win->len = (win->x * win->y);
		return ch;
	}
	*win->rp = ch;
	return *win->rp++;
}

