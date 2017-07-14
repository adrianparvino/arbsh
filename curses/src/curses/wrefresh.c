#include <curses.h>



typedef struct range {
	size_t o;
	size_t l;
}range[1000];

int _simple_refresh(WINDOW *win)
{
	size_t i = 1;
	size_t j = 0;
	size_t k = 1;
	
	static char last[4096] = { 0 };
	//write(win->fd, win->buf, win->rp - win->buf);
	for (i=0;i< (win->rp - win->buf);++i,++k)
	{
		if ( k == COLS )
		{
			k = 1;
			++j;
		}
		
		if ( last[i] != win->buf[i])
		{
			_setcursor(k, j);
			write(win->fd, win->buf[i], 1);
			last[i] = win->buf[i];
		}
		
	}
}


int wrefresh(WINDOW *win)
{
	char buf[32];
	size_t len = 0;
	_setcursor(1, 0);
	clrtobot();
	if (win->clearok == 1)
	{
		len = sprintf(buf, "%s", ansiglb.t_eraseall);
		write(win->fd, buf, len);
	}
	_simple_refresh(win);
	//write(win->fd, win->buf, win->rp - win->buf);
	//size_t i = 0;
	/*
	for ( ; i < win->len ; ++i)
	{
		if (!(win->last[i] != win->buf[i]))
		{
			range[k].o = i;
			for ( ; i < win->len ; ++i)
				if (!(win->last[i] != win->buf[i]))
				{
					range[k].l++;
					win->last[i] = win->buf[i];
				}
			k++;
		} 
	}
	*/
	win->rp = win->buf;
	_setcursor(win->px, win->py);
	return 0;
}
