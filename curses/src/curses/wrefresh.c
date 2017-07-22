#include <curses.h> 

int wrefresh(WINDOW *win)
{
	char buf[32];
	size_t len = 0;
	
	_setcursor(0, 1);
	//write(1, "fuck\n\n\n", 7);
	clrtobot();
//	if (win->clearok == 1)
//	{
	//	len = sprintf(buf, "%s", ansiglb.t_eraseall);
	//	write(win->fd, buf, len);
	//	_setcursor(1, 1);
//	}

	size_t i = 0;
	size_t j = 1;
	size_t k = 1; 
	static char last[10000] = { 0};
	

	for (;i < (win->rp - win->buf) ; ++i)
	{ 


		_setcursor(k, j); 
                write(1, win->buf + i, 1); 

	
		
		
                if (j == COLS ) 
                {
                        j = 1;
                        ++k;
                } else ++j;
	}
	_setcursor(win->px, win->py + 1); 

        win->rp = win->buf;
        win->len = (win->x * win->y);
	return 0;
}
