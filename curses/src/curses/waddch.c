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
		if ((win->last = malloc(sizeof(char) * win->len)) == NULL)
		{
			win->len = 0;
			return -1;
		}

		win->rp = win->buf;
	} 
	
	*win->rp = ch;
	win->rp++; 
	
	return ch;
}

