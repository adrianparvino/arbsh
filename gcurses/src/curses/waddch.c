#include <gcurses/gcurses.h>

int waddch(WINDOW *win, chtype ch)
{
	chtype ret = 0;
	if ( win->buf == NULL )
	{
		win->len =(win->x * win->y);
		if ((win->buf = malloc(sizeof(char) * win->len)) == NULL)
		{
			win->len = 0;
			return -1;
		}
		win->buf = win->rp;
	}
	if ( win->len > 0 )
	{
		win->len--;
	}
	*win->rp = ch;
	ret = ch;
	*win->rp++;
	return ret;
}
