#include <curses.h>

void simple_refresh(WINDOW *win)
{
	size_t i, j, k;
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

}

void clear_ok_wrap(WINDOW *win)
{
	char buf[32];
	size_t len = 0; 
        if (win->clearok == 1)
        {
                _setcursor(0, 1); 
                len = sprintf(buf, "%s", ansiglb.t_eraseall);
                write(win->fd, buf, len); 
        } 
}

void line_refresh(WINDOW *win)
{ 
	size_t i, j, k;
	int lines[4096] = { 0 };
	for (i=0, j=1, k=1;i < (win->rp - win->buf) ; ++i)
	{ 
		/* a character is dirty mark the current line for redrawing */
		if (win->last[i] != win->buf[i] ) 
			lines[k] = 1;
	
                if (j == win->x ) 
                {
                        j = 1;
                        ++k;
                } 
		else 
			++j;
	} 
	/* iterate through all lines */
	for (i=0,j=1; i<(win->rp - win->buf);i+=(win->x), ++j)
	{
		/* A line was dirty, position the cursor and redraw it */
		if (lines[j])
		{
			_setcursor(j, 0);
			write(1, win->buf + i, win->x);
			memcpy(win->last + i, win->buf + i, win->x);
		}
	}
}

int wrefresh(WINDOW *win)
{
	/* actually draw the chaacter grid */
	//simple_refresh(win);
	line_refresh(win);

	/* set the final user cursor position */
	_setcursor(win->px, win->py + 1); 

	/* reset the buffer pointer and the len count */
        win->rp = win->buf;
        win->len = (win->x * win->y);

	return 0;
}
