#include <gcurses/gcurses.h>

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
		win->buf = win->rp;
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

