#include "fcntl.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <termcap/vt100.h>

#define CURSES_MAX 10
#define CURSES_BUFSIZ 512

typedef struct{ 
	int fd;
	char flags;
	char *buf;
	char *rp;
	char *lp;
	ssize_t pid;
        size_t counter;
        char *ansiwinbuf;
        char *ansilastmap;
        char *cpairs[CURSES_BUFSIZ];
        int colordlen[CURSES_BUFSIZ];
        char *colorlast[CURSES_BUFSIZ];
} WINDOW;

extern WINDOW _IO_canon[CURSES_MAX];

enum _canons {
	_BLACK  = 001,
	_RED_ = 002,
	_GREEN = 004,
	_WHITE = 030,
	_YELLOW  = 010,
	_BLUE  = 020,
};

struct ansiglb{
        size_t row;     /* global rows    */
        size_t col;     /* global columns */
        size_t t;       /* total windows  */
        size_t c;       /* current window */
}ansiglb;


#define stdscr  (&_IO_canon[0])

int wmove(WINDOW *, size_t, size_t);
int move(size_t, size_t);
WINDOW *initscr(void);

int addch(const char);
int waddch(WINDOW *, const char);
int mvaddch(int, int, const char);
int mvwaddch(WINDOW *, int, int, const char);
int echochar(const char);
int wechochar(WINDOW *, const char);
