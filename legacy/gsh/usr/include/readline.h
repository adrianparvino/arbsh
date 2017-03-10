#include <stddef.h>
#include <gstdio.h>
#include <termcap.h>
#include <gstring.h>

#include <stdlib.h>
/*
	2017 (C) Copyright, readline.h, CM Graff
*/

/* function prototypes */ 
size_t ircline(char *, char *, size_t);
void ircprint(char *, size_t, char *, size_t); 
void determinewin(void); 
static int readchar(void);
size_t greadline(char *, char *, size_t);
size_t greadgetch(char *);
void greadprint(char *, size_t, char *, size_t);
int gread_history(char *, size_t);

/* structures */
struct hglb {		/* globals	*/
	size_t t;	/* Total	*/
	size_t c;	/* Current	*/
	int r;		/* Runstate	*/
	size_t laro;	/* left arrow(s)*/ 
	size_t w;
	size_t h;
}hglb;


struct hist {			/* history lines	*/
	char line[GBUFSIZ];	/* lines		*/ 
	size_t len;		/* line length		*/
}*hist;

struct winsize win;
