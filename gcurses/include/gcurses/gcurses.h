#include "fcntl.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <termcap/vt100.h>

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
}ansiglb;

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


/* internal */
int _termcatch(int, int);

/* refresh */
int refresh(void);
int wrefresh(WINDOW *win);

