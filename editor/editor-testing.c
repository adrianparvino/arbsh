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
int tabstop = 8;

/* macros */
#define	TRUE	1
#define	FALSE	0
#define	LINSIZ	128 

/* function prototypes */
void *ecalloc(size_t, size_t);
void *erealloc(void *, size_t); 
size_t edgetch(void);
void f_delete(void);
void f_insert(void);
void i_calcvlen(struct Line * l); 
bool i_deltext(struct filepos, struct filepos);
void i_die(const char *str); 
void i_edit(void); 
void i_readfile(void);
void i_setup(void); 
void i_sortpos(struct filepos *, struct filepos *);
void i_update(void); 
bool i_writefile(char *);
struct filepos i_addtext(char *, struct filepos); 
struct filepos m_nextchar(struct filepos);
struct filepos m_prevchar(struct filepos);
struct filepos m_nextline(struct filepos);
struct filepos m_prevline(struct filepos);
void getdimensions(void);
static void sigwinch(int);
int vlencnt(int, int);
int vlinecnt(struct Line *);


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
		l->vlen += vlencnt(l->c[i], l->vlen);
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

void getdimensions(void)
{
	cols = ansiglb.col;
	lines = ansiglb.row; 
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
			getdimensions();
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
	getdimensions();
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
	for(l = fstline, iline = 1;
		l && scrline->prev && l != scrline; iline++, l = l->next) {
		if(l == fcur.l) { /* Can't have fcur.l before scrline, move scrline up */
			i = 0;
			while(l != scrline) {
				if(vlinecnt(scrline) > 1) {
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
		vlines = vlinecnt(l);
		if(fcur.l == l) { 
			/* Can't have fcur.l after screen end, move scrline down */
			while(irow + vlines > lines && scrline->next) {
				irow -= vlinecnt(scrline);
				i += vlinecnt(scrline); 
				scrline = scrline->next;
				iline++;
			}
			break;
		}
	} 
	/* end scroll area ? */ 
	
	/* Actually update lines on screen */
	for(irow = 1 , l = scrline; irow < lines;
		irow += vlines, iline++) {
		vlines = vlinecnt(l);
		if(fcur.l == l) { 
			/* Update screen cursor position */
			cursor_c = 0;
			cursor_r = irow;
			for(ichar = 0; ichar < fcur.o; ichar++)
				cursor_c += vlencnt(fcur.l->c[ichar], cursor_c);
			while(cursor_c >= cols) {
				cursor_c -= cols;
				cursor_r++;
			}
		} 
		if(l)
			l->dirty = FALSE; 
		for(ixrow = ichar = ivchar = 0; ixrow < vlines && (irow + ixrow) < lines; ixrow++)
		{
			setcursor((irow + ixrow ), (ivchar % cols));
			while(ivchar < (1 + ixrow) * cols)
			{
				if(l && ichar < l->len) {
					/* Tab nightmare */
					if(l->c[ichar] == '\t') { 
						write(1, WHITESPACE, vlencnt('\t', ivchar));
					}
					else {
						write(1, l->c + ichar, 1);
					}
					ivchar += vlencnt(l->c[ichar], ivchar);
					ichar++;
				} else { 
					//write(1, " ", 1);
					write(1, T_CLRCUR2END, T_CLRCUR2END_SZ);
					ivchar++;
					ichar++;
				}
				
			}
			
		} 
		if(l)
			l = l->next;
			
	} 
	/* Position cursor  ?? */
	setcursor(cursor_r, cursor_c  + 1); 
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
		ivchar += vlencnt(pos.l->c[ichar], ivchar); 
	if(pos.l->next) { 
		for(pos.l = pos.l->next, pos.o = ichar = 0; ichar < ivchar && pos.o < pos.l->len; pos.o++)
			ichar += vlencnt(pos.l->c[pos.o], ichar); 
	} else {
		pos.o = pos.l->len;
	}
	return pos;
} 

struct filepos m_prevline(struct filepos pos) {
	size_t ivchar, ichar; 
	for(ivchar = ichar = 0; ichar < pos.o; ichar++)
		ivchar += vlencnt(pos.l->c[ichar], (ivchar % (cols - 1))); 
	if(pos.l->prev) { 
		for(pos.l = pos.l->prev, pos.o = ichar = 0; ichar < ivchar && pos.o < pos.l->len; pos.o++)
			ichar += vlencnt(pos.l->c[pos.o], ichar); 
	} else {
		pos.o = 0;
	}
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

int vlencnt(int ch, int col)
{
	if ( ch == '\t' )
		return tabstop - (col % tabstop);
	return 1;
}

int vlinecnt(struct Line *l)
{
	if ( l )
		return ( 1 + ( l->vlen / cols));
	return 1;
}
