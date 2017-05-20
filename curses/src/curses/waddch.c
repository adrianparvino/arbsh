#include <curses.h>

int waddch(WINDOW *win, chtype ch)
{
	
	if (win->buf == NULL)
	{
		write(1,"was here", 10);
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

	*win->rp = ch;
	
	if (win->len == 0)
	{
		wrefresh(win);
		win->buf = win->rp;
		win->len = (win->x * win->y);
		return ch;
	}
	return *win->rp++;
}

