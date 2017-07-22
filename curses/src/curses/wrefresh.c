#include <curses.h>

typedef struct range {
	size_t o;
	size_t l;
}range[1000];


int wrefresh(WINDOW *win)
{
	char buf[32];
	size_t len = 0; 
	size_t i, j, k;
	
	/*
	if (win->clearok == 1)
	{
		_setcursor(0, 1); 
		len = sprintf(buf, "%s", ansiglb.t_eraseall);
		write(win->fd, buf, len); 
	}
	*/

	for (i=0, j=1, k=1;i < (win->rp - win->buf) ; ++i)
	{ 
		if (win->last[i] != win->buf[i] )
		{
			_setcursor(k, j);
			write(1, win->buf + i, 1);
			win->last[i] = win->buf[i];
		}
	
                if (j == COLS ) 
                {
                        j = 1;
                        ++k;
                } 
		else 
			++j;
	}

	/* set the final user cursor position */
	_setcursor(win->px, win->py + 1); 

	/* reset the buffer pointer and the len count */
        win->rp = win->buf;
        win->len = (win->x * win->y);

	return 0;
}
