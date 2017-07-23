#include <curses.h>

void _simple_refresh(WINDOW *win)
{
        size_t i, j, k;
        for (i=0, j=1, k=1;i < (win->rp - win->buf) ; ++i)
        {
                if (win->last[i] != win->buf[i] )
                {
                        _setcursor(k, j);
                        write(win->fd, win->buf + i, 1);
                        win->last[i] = win->buf[i];
                }
                if (j == win->x )
                {
                        j = 1;
                        ++k;
                } else ++j;
        }
}

void _clear_ok_wrap(WINDOW *win)
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
