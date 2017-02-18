/*
	Copyright 2016-2017, CM Graff, hexen.h 
*/
#include <termios.h>
#include <sys/ioctl.h>
#include "termcap.h"
#include "../libc/string/string.h"
#include "../libc/stdio/stdio.h"
#include "../libc/stdlib/stdlib.h"

int dothink;
int hardadd;

struct ansiglb{
	size_t row;	/* global rows    */
	size_t col;	/* global columns */
	size_t t;	/* total windows  */
	size_t c;	/* current window */
};//ansiglb;// = { 0, 0, 0, 0};

struct ANSIWINDOW{
	size_t len;		/* length of primary buffer 	*/
	size_t counter;		/* A countdown mechanism	*/
	char *ansiwinbuf;	/* primary buffer 		*/
	char *ansilastmap;	/* last buffer printed 		*/
	char *cpairs[GBUFSIZ];
	int colordlen[GBUFSIZ];
	char *colorlast[GBUFSIZ];
};//ANSIWINDOW;//[15] = {{ 0,0, GNULL, GNULL, { GNULL } , { 0 } , {GNULL}}};

/* fumction prototypes */ 
int fastgetch(void);
int ansigetch(void);
int termcatch(int, int);
void setcursor(size_t, size_t);
void setcursorchars(size_t, size_t, char);
void ansihorizon(size_t, size_t);
int ansiinit(void);
void addcolor(char *, size_t, size_t);
void addcolorrange(char *, size_t, size_t, size_t);
int ansicreate(void);
int ansidestroy(void);
int ansiwaddch(int, int);
int ansiaddmem(char *, int, size_t);
size_t ansiaddstr(char *, size_t);
int ansiredraw(size_t, size_t, size_t, size_t);
