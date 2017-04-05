#include "fcntl.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <gtermcap/vt100.h>

/* limits */
#define CURSES_MAX 10
#define CURSES_BUFSIZ 512

/* data types */
typedef char chtype;

typedef struct{ 
	int fd;
	char flags;
	char *rp;
        size_t len;
        char *buf;
        char *last;
        char *cpairs[CURSES_BUFSIZ];
        int colordlen[CURSES_BUFSIZ];
        char *colorlast[CURSES_BUFSIZ];
	size_t x;				/* dimensions */
	size_t y;				/* dimensions */
} WINDOW;

extern WINDOW _IO_canon[CURSES_MAX];

/* bit masks */
enum _canons {
	_BLACK  = 001,
	_RED_ = 002,
	_GREEN = 004,
	_WHITE = 030,
	_YELLOW  = 010,
	_BLUE  = 020,
};

/* global structures */
struct ansiglb{
        size_t row;     /* global rows    */
        size_t col;     /* global columns */
        size_t t;       /* total windows  */
        size_t c;       /* current window */
	char *t_eraseall;	/* terminal capability */
	char *t_insertreset;	/* terminal capability */
	char *t_gohome;		/* terminal capability */
	char *t_clrcur2bot;	/* terminal capability */
	char *t_clrtoeol;	/* terminal capability */
} ansiglb;

/* macros */
#define stdscr  (&_IO_canon[0])

/** functions **/

/* cursor moving */
int wmove(WINDOW *, size_t, size_t);
int move(size_t, size_t);
/* initialize */
WINDOW *initscr(void);
/* character io */
int addch(chtype); 				/* not implemented */
int waddch(WINDOW *, const chtype); 		/* not implemented */
int mvaddch(int, int, const chtype); 		/* not implemented */
int mvwaddch(WINDOW *, int, int, const chtype); /* not implemented */
int echochar(const chtype); 			/* not implemented */
int wechochar(WINDOW *, const chtype); 		/* not implemented */
/* colorization */
int start_color(void); 				/* not implemented */
bool has_colors(void);				/* not implemented */
bool can_change_color(void);			/* not implemented */
int init_pair(short pair, short f, short b);	/* not implemented */
int init_color(short color, short r, short g, short b);	/* not implemented */ 
/* echo */
int noecho(void);
int echo(void);
/* internal */
int _termcatch(int, int);
/* refresh */
int refresh(void);
int wrefresh(WINDOW *win);
/* erase */
int erase(void);				/* not implemented */
int werase(WINDOW *);				/* not implemented */
int clear(void);				/* not implemented */
int wclear(WINDOW *);				/* not implemented */
int clrtobot(void);				/* not implemented */
int wclrtobot(WINDOW *);			/* not implemented */
int clrtoeol(void);				/* not implemented */
int wclrtoeol(WINDOW *);			/* not implemented */
