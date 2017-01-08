#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h>
#include <locale.h>
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <signal.h> 
#include <sys/types.h>
#include "../lib/hexen.h" 


/*
	See LICENSE file for copyright and license details. 
*/ 


/* structs */
struct Line {		/** The internal representation of a line of text */
	char *c;	/* struct Line content */
	size_t len;	/* struct Line byte length */
	size_t vlen;	/* On-screen line-length */
	size_t mul;	/* How many times LINSIZ is c malloc'd to */
	bool dirty;	/* screen should be repainted */
	struct Line *next;	/* Next line, NULL if last */
	struct Line *prev;	/* Previous line, NULL if first */
} Line;

struct filepos {	/** A position in the file */
	struct Line *l;	/* struct Line */
	size_t o;	/* Offset inside the line */
} filepos;

/* Globals */
int running = 1; 
struct Line *fstline;	/* First line */
struct Line *lstline;	/* Last line  */
struct Line *scrline;	/* First line seen on screen */
struct filepos fsel;	/* Selection point on file   */
struct filepos fcur;	/* Insert position on file, cursor, current position */
int ch = 0;		/* Used to store input */
char c[7] = { 0 };	/* Used to store input */ 
char *fname = NULL;
int cols = 0;
int lines = 0;
int winchg = 0;
int cflags = 0;
int topmarg = 0;
int bottommarg = 0; 
int leftmarg = 0; 
int rightmarg = 0;
int tabstop = 8; 


/* macros */
#define TRUE 1
#define FALSE 0
#define LINSIZ		128
#define VLEN(ch,col)  (ch=='\t' ? tabstop - (col%tabstop) : 1)
#define VLINES(l)	 (1+(l?l->vlen/cols:0))


/* function prototypes */
void *ecalloc(size_t, size_t);
void *erealloc(void *, size_t); 
void f_delete(void);
void f_insert(void); 
size_t edgetch(void);
struct filepos i_addtext(char *, struct filepos); 
void i_calcvlen(struct Line * l); 
bool i_deltext(struct filepos, struct filepos);
void i_die(const char *str); 
void i_edit(void); 
void i_readfile(void);
void i_setup(void); 
void i_sortpos(struct filepos *, struct filepos *);
void i_update(void); 
bool i_writefile(char *); 
struct filepos m_bol(struct filepos); 
struct filepos m_nextchar(struct filepos);
struct filepos m_prevchar(struct filepos);
struct filepos m_nextline(struct filepos);
struct filepos m_prevline(struct filepos);
struct filepos m_nextscr(struct filepos);
struct filepos m_prevscr(struct filepos); 
void normalizetoscr(void);
static void sigwinch(int);


int main(int argc, char *argv[])
{ 

	if ( argc < 2 ) 
	{
		write(2, "Requires a file to edit\n", 24);
		return 1;
	}

	
	setlocale(LC_ALL, ""); 

	termcatch(~(ICANON | ECHO), 0);
	signal(SIGWINCH, sigwinch);
	i_setup();
	fname = argv[1];
	i_readfile();
	i_edit();
	i_die("");
	return 0;
} 

void *ecalloc(size_t nmemb, size_t size)
{
	void *p; 
	p = calloc(nmemb, size);
	if(p == NULL)
		i_die("Can't calloc.\n");
	return p;
}

void *erealloc(void *ptr, size_t size)
{
	void *p; 
	p = realloc(ptr, size);
	if(p == NULL)
		i_die("Can't realloc.\n"); 
	return p;
}

void f_delete(void)
{ 
	struct filepos pos0 = fcur;
	struct filepos pos1 = (struct filepos)m_prevchar(fcur);
	
	i_sortpos(&pos0, &pos1);
	
	if(i_deltext(pos0, pos1)) 
		fcur = pos0;
	else
		fcur = fsel = pos0;
}

void f_insert(void)
{
	struct filepos newcur;
	newcur = i_addtext((char *) c, fcur);
	if(fcur.l != newcur.l)
		fsel = newcur;

	fcur = fsel = newcur; 
} 


/* Add text at pos, return the position after the inserted text */
struct filepos i_addtext(char *buf, struct filepos pos)
{
	struct Line *l = pos.l, *lnew = NULL; 
	size_t o = pos.o, i = 0, il = 0;
	struct filepos f;
	char c; 
	
	for(c = buf[0]; c != '\0'; c = buf[++i]) { 
		/* newline / line feed */
		if(c == '\n' || c == '\r') {
			lnew = (struct Line *)ecalloc(1, sizeof(struct Line));
			lnew->c = ecalloc(1, LINSIZ);
			lnew->dirty = l->dirty = TRUE;
			lnew->len = lnew->vlen = 0;
			lnew->mul = 1;
			lnew->next = l->next;
			lnew->prev = l;
			if(l->next)
				l->next->prev = lnew;
			else
				lstline = lnew;
			l->next = lnew;
			l = lnew;
			/* \n in the middle of a line */ 
			if(o + il < l->prev->len) {
				f.l = l;
				f.o = 0;
				i_addtext(&(l->prev->c[o + il]), f);
				l->prev->len = o + il;
				l->prev->c[o + il] = '\0';
			}
			i_calcvlen(l->prev);
			o = il = 0; 
		} else {
			/* Regular char */
			if(2 + (l->len) >= LINSIZ * (l->mul))
				l->c = (char *) erealloc(l->c, LINSIZ * (++(l->mul)));
			memmove(l->c + il + o + 1, l->c + il + o, (1 + l->len - (il + o)));
			l->c[il + o] = c;
			l->dirty = TRUE;
			if(il + o >= (l->len)++)
				l->c[il + o + 1] = '\0';
			il++;
		}
	}
	i_calcvlen(l);
	f.l = l;
	f.o = il + o; 
	return f;
}

/* Update the vlen value of a struct Line */
void i_calcvlen(struct Line * l)
{
	size_t i; 
	l->vlen = 0;
	for(i = 0; i < l->len; i++)
		l->vlen += VLEN(l->c[i], l->vlen);
} 

void i_die(const char *str)
{ 
	termcatch(~(ICANON | ECHO), 1);
	write(2, str, strlen(str)); 
	exit(1);
}

/* Delete text between pos0 and pos1, which MUST be in order, fcur integrity
   is NOT assured after deletion, fsel integrity is returned as a bool */
bool i_deltext(struct filepos pos0, struct filepos pos1)
{
	struct Line *ldel = NULL; 
	bool integrity = TRUE; 

	if(pos0.l == fsel.l)
		integrity = (fsel.o <= pos0.o || (pos0.l == pos1.l
			&& fsel.o > pos1.o));
	if(pos0.l == pos1.l) { 
		memmove(pos0.l->c + pos0.o, pos0.l->c + pos1.o,
			(pos0.l->len - pos1.o));
		pos0.l->dirty = TRUE;
		pos0.l->len -= (pos1.o - pos0.o);
		pos0.l->c[pos0.l->len] = '\0';
		i_calcvlen(pos0.l); 
	} else { 

		pos0.l->len = pos0.o;
		pos0.l->c[pos0.l->len] = '\0';
		pos0.l->dirty = TRUE; // <<-- glitch in screen updates! 
		// i_calcvlen is unneeded here, because we call i_addtext later
		while(pos1.l != ldel) {
			if(pos1.l == pos0.l->next)
				i_addtext(&(pos0.l->next->c[pos1.o]), pos0);
			if(pos0.l->next->next)
				pos0.l->next->next->prev = pos0.l;
			ldel = pos0.l->next;
			pos0.l->next = pos0.l->next->next;
			if(scrline == ldel)
				scrline = ldel->prev;
			if(lstline == ldel)
				lstline = ldel->prev;
			if(fsel.l == ldel)
				integrity = FALSE;
			free(ldel->c);
			free(ldel);
		}
	} 

	return integrity;
} 

void normalizetoscr(void)
{
	cols = ansiglb.col;
	lines = ansiglb.row;
	if ( lines > topmarg )
		lines -= topmarg;
	if ( lines > topmarg )
		lines -= bottommarg;
	if ( cols > leftmarg )
		cols -= leftmarg;
	if ( cols > rightmarg )
		cols -= rightmarg;
}

/* Main editing loop */
void i_edit(void)
{ 
	while ( running )
	{ 
		dothink = 0;
		if ( winchg == 1 )
		{ 
			dothink = 1; 
			ansiinit(); 
			normalizetoscr();
			winchg=0; 
		}
		i_update(); 
		edgetch();
	}
} 

void i_readfile(void)
{
	int fd;
	ssize_t n;
	char *buf = NULL; 

	if((fd = open(fname, O_RDONLY)) == -1) { 
		i_die("unable to open file\n");
	} 

	buf = ecalloc(1, BUFSIZ + 1);
	while((n = read(fd, buf, BUFSIZ)) > 0) {
		buf[n] = '\0';
		fcur = i_addtext(buf, fcur);
	}
	fcur.l = fstline;
	fcur.o = 0;
	fsel = fcur; 
} 

void i_setup(void) 
{
	struct Line *l = NULL; 
	
	ansiinit();
	normalizetoscr();
	ansicreate();
	/* Init line structure */
	l = (struct Line *) ecalloc(1, sizeof(struct Line));
	l->c = ecalloc(1, LINSIZ);
	l->dirty = FALSE;
	l->len = l->vlen = 0;
	l->mul = 1;
	l->next = NULL;
	l->prev = NULL; 
	fstline = lstline = scrline = fcur.l = l;
	fcur.o = 0;
	fsel = fcur; 

	return; 
} 

/* Exchange pos0 and pos1 if not in order */
void i_sortpos(struct filepos * pos0, struct filepos * pos1)
{
	struct filepos p;

	for(p.l = fstline; p.l; p.l = p.l->next) {
		if(p.l == pos0->l || p.l == pos1->l) {
			if((p.l == pos0->l && (p.l == pos1->l
					&& pos1->o < pos0->o)) || (p.l == pos1->l
				&& p.l != pos0->l))
				p = *pos0, *pos0 = *pos1, *pos1 = p;
			break;
		}
	}
}

	
/* Repaint screen */ 
void i_update(void)
{
	int iline, irow, ixrow, ivchar, i, vlines;
	int cursor_r = 0, cursor_c = 0;
	size_t ichar; 
	struct Line *l;
	
	/* Check offset */
	size_t lim = 0;

	for(l = fstline, iline = 1;
		l && scrline->prev && l != scrline; iline++, l = l->next) {
		if(l == fcur.l) { /* Can't have fcur.l before scrline, move scrline up */
			i = 0;
			while(l != scrline) {
				if(VLINES(scrline) > 1) {
					i = -1;
					break;
				}
				i++;
				scrline = scrline->prev;
			}
			if(i < 0 || i > lines) {
				scrline = l; 
			}
			break;
		} 
	}
	for(i = irow = 1, l = scrline; l; l = l->next, irow += vlines) { 
		vlines = VLINES(l);
		if(fcur.l == l) { 
			/* Can't have fcur.l after screen end, move scrline down */
			while(irow + vlines > lines && scrline->next) {
				irow -= VLINES(scrline);
				i += VLINES(scrline); 
				scrline = scrline->next;
				iline++;
			}
			break;
		}
	} 
	/* end scroll area ? */ 
	
	/* Actually update lines on screen */ 
	//in = 0;
	for(irow = 1 , l = scrline; irow < lines;
		irow += vlines, iline++) {
		vlines = VLINES(l);
		if(fcur.l == l) { 
			/* Update screen cursor position */
			cursor_c = 0;
			cursor_r = irow;
			for(ichar = 0; ichar < fcur.o; ichar++)
				cursor_c += VLEN(fcur.l->c[ichar], cursor_c);
			while(cursor_c >= cols) {
				cursor_c -= cols;
				cursor_r++;
			}
		} 
		if(l)
			l->dirty = FALSE; 
		for(ixrow = ichar = ivchar = 0; ixrow < vlines && (irow + ixrow) < lines; ixrow++)
		{
			//setcursor((irow + ixrow ) + 1, (ivchar % cols) + 1);
			while(ivchar < (1 + ixrow) * cols)
			{
				if(l && ichar < l->len) {
			
						
					/* Tab nightmare */
					if(l->c[ichar] == '\t') {
						for(i = 0; i < VLEN('\t', ivchar); i++)
							ansiwaddch(' ', lim++);
					}
					else {
						ansiwaddch(l->c[ichar], lim++);
					}
					ivchar += VLEN(l->c[ichar], ivchar);
					ichar++;
				} else {
					ansiwaddch(' ', lim++);
					ivchar++;
					ichar++;
				}
			}
		} 
		if(l)
			l = l->next;
			
	}
	ansiglb.c = 0;
	ansiredraw(lim, topmarg, leftmarg, rightmarg);
	
	/* Position cursor  ?? */
	setcursor(cursor_r + topmarg, cursor_c + 1 + leftmarg); 
	dothink = 0;
} 

bool i_writefile(char *fname)
{
	int fd = 1; 
	bool wok = TRUE;
	struct Line *l; 

	if(fname != NULL
		&& (fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
			S_IWOTH)) == -1) {
		/* error */ 
		return FALSE;
	} 
	for(l = fstline; wok && l; l = l->next) {
		if(write(fd, l->c, l->len) == -1 || (l->next && write(fd, "\n", 1) == -1))
			wok = FALSE;
	} 
	close(fd);
	return wok;
}

struct filepos m_bol(struct filepos pos) {
	pos.o = 0;
	return pos;
}

struct filepos m_nextchar(struct filepos pos) {
	if(pos.o < pos.l->len) {
		pos.o++; 
	} else if(pos.l->next) {
		pos.l = pos.l->next;
		pos.o = 0;
	}
	return pos;
} 

struct filepos m_prevchar(struct filepos pos) {
	if(pos.o > 0) {
		pos.o--; 
	} else if(pos.l->prev) {
		pos.l = pos.l->prev;
		pos.o = pos.l->len;
	}
	return pos;
} 

struct filepos m_nextline(struct filepos pos) {
	size_t ivchar, ichar; 
	for(ivchar = ichar = 0; ichar < pos.o; ichar++)
		ivchar += VLEN(pos.l->c[ichar], ivchar); 
	if(pos.l->next) { 
		for(pos.l = pos.l->next, pos.o = ichar = 0; ichar < ivchar && pos.o < pos.l->len; pos.o++)
			ichar += VLEN(pos.l->c[pos.o], ichar); 
	} else {
		pos.o = pos.l->len;
	}
	return pos;
} 

struct filepos m_prevline(struct filepos pos) {
	size_t ivchar, ichar; 
	for(ivchar = ichar = 0; ichar < pos.o; ichar++)
		ivchar += VLEN(pos.l->c[ichar], (ivchar % (cols - 1))); 
	if(pos.l->prev) { 
		for(pos.l = pos.l->prev, pos.o = ichar = 0; ichar < ivchar && pos.o < pos.l->len; pos.o++)
			ichar += VLEN(pos.l->c[pos.o], ichar); 
	} else {
		pos.o = 0;
	}
	return pos;
} 

struct filepos m_nextscr(struct filepos pos) {
	int i;
	struct Line *l; 
	for(i = lines, l = pos.l; l->next && i > 0; i -= VLINES(l), l = l->next)
		;
	pos.l = l;
	pos.o = pos.l->len;
	return pos;
} 

struct filepos m_prevscr(struct filepos pos) {
	int i;
	struct Line *l; 
	for(i = lines, l = pos.l; l->prev && i > 0; i -= VLINES(l), l = l->prev)
		;
	pos.l = l;
	pos.o = 0;
	return pos;
} 

size_t edgetch(void)
{
	static size_t len = 0; 
	  
	ch = getch(); 

	switch (ch) { 
	case K_ESCAPE: 
		ch = getch(); 
		switch (ch) {
			case '[': 
				ch = getch(); 
				switch (ch) { 
					case 'A': /* arrow up */ 
						fcur = m_prevline(fcur); 
						break;
					case 'B': /* arrow down */ 
						fcur = m_nextline(fcur); 
						break;
					case 'C': /* right arrow */ 
						fcur = m_nextchar(fcur); 
						break;
					case 'D': /* left arrow */ 
						fcur = m_prevchar(fcur); 
						break;
					case 'H': /* Home */ 
						fcur = m_bol(fcur);
						ch = getch(); 
						break;
					case '5': /* page up */ 
						fcur = m_prevscr(fcur);
						ch = getch(); 
						break; 
					case '6': /* page down */ 
						fcur = m_nextscr(fcur);
						ch = getch(); 
						break;
			}
		}
		return len;
	case K_BACKSPACE:
		f_delete();
		break;
	case K_CTRLEXX:
		i_writefile(fname);
		break;
	case K_CTRLENN:
		i_die("");
		break; 
	default:
		c[0] = (char) ch;
		f_insert();
		break;
	}
	return len;
}

static void sigwinch(int sig)
{
	if (sig)
		winchg = 1;
}
