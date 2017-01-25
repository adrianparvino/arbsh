/*
	See LICENSE file for copyright and license details. 
*/ 

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
#include <regex.h> 
#include "../lib/hexen.h" 

#define TRUE 1
#define FALSE 0 
#define TOTMAPS 5

/* regex globals */
char COLORS[TOTMAPS][50] = { 
T_BLUE_FG,
T_YELLOW_FG,
T_GREEN_FG, 
T_RED_FG,
T_MAGENTA_FG 
}; 

char MAPS[TOTMAPS + 1][200] = { 
"^(//.*|\\/\\*.*\\*/)",
"^(if|else|while|for|do|default|break|return|case|switch)",
"^(int|char|size_t|static|void|unsigned|bool|typedef|struct)",
"^(\".*\"|<.*\\.[ch]>|NULL|BUFSIZ|PATH_MAX|[0-9]*|'.')",
"^(#define .*|#include|'..')",
".*\\.[ch]$"	/* file suffix match ( always last )*/
}; 

regex_t re[TOTMAPS + 1];
regmatch_t rm[TOTMAPS + 1][2]; 

regex_t rein;
regmatch_t rmin[2];

regex_t reout;
regmatch_t rmout[2];

int cflags = 0;
int regexon = 0;
int topmarg = 0;
int bottommarg = 0; 
int leftmarg = 0; 
int rightmarg = 0;
int inacomment = 0;
static int tabstop = 8; 

#define LINSIZ		128 
#define VLEN(ch,col)  (ch=='\t' ? tabstop - (col%tabstop) : 1)
#define VLINES(l)	 (1+(l?l->vlen/cols:0)) 

/* Typedefs */
typedef struct Line Line;

struct Line {		/** The internal representation of a line of text */
	char *c;	/* Line content */
	size_t len;	/* Line byte length */
	size_t vlen;	/* On-screen line-length */
	size_t mul;	/* How many times LINSIZ is c malloc'd to */
	bool dirty;	/* screen should be repainted */
	Line *next;	/* Next line, NULL if last */
	Line *prev;	/* Previous line, NULL if first */
};

typedef struct {	/** A position in the file */
	Line *l;	/* Line */
	size_t o;	/* Offset inside the line */
} Filepos;

/* Variables */
int running = 1; 
static Line *fstline;	/* First line */
static Line *lstline;	/* Last line  */
static Line *scrline;	/* First line seen on screen */
static Filepos fsel;	/* Selection point on file   */
static Filepos fcur;	/* Insert position on file, cursor, current position */ 

static int ch;		/* Used to store input */
static char c[7];	/* Used to store input */ 
static char *fname = NULL;
static int cols;
static int lines;
int winchg = 0;

static void *ecalloc(size_t, size_t);
static void *erealloc(void *, size_t);

static void f_delete(void);
static void f_insert(void); 

size_t edfastgetch(void);
static Filepos i_addtext(char *, Filepos); 
static void i_calcvlen(Line * l); 
static bool i_deltext(Filepos, Filepos);
static void i_die(const char *str); 
static void i_edit(void); 
static void i_readfile(void);
static void i_setup(void); 
static void i_sortpos(Filepos *, Filepos *);
static void i_update(void); 
static bool i_writefile(char *); 

static Filepos m_bol(Filepos); 
static Filepos m_nextchar(Filepos);
static Filepos m_prevchar(Filepos);
static Filepos m_nextline(Filepos);
static Filepos m_prevline(Filepos);
static Filepos m_nextscr(Filepos);
static Filepos m_prevscr(Filepos); 
void highlight(char *, int, size_t); 
void normalizetoscr(void);

static void sigwinch(int sig)
{
	if (sig)
		winchg = 1;
}


int main(int argc, char *argv[])
{ 
	
	size_t i = 0;

	if ( argc < 2 ) 
	{
		write(2, "Requires a file to edit\n", 24);
		return 1;
	}

	
	setlocale(LC_ALL, ""); 
	regcomp(&re[TOTMAPS],MAPS[TOTMAPS], cflags);

	regcomp(&rein, "\\/\\*", cflags);
	regcomp(&reout, "\\*/)", cflags);

	if (((regexec(&re[TOTMAPS], argv[1], 0, 0, 0)) == 0))
	{
		cflags |= REG_EXTENDED; 
		
		for ( i = 0;i < TOTMAPS ;i++)
			regcomp(&re[i], MAPS[i], cflags); 
		regexon = 1;
	}

	termcatch(~(ICANON | ECHO), 0);
	signal(SIGWINCH, sigwinch);
	i_setup();
	fname = argv[1];
	i_readfile();
	i_edit();
	i_die("");
	return 0;
} 

static void *ecalloc(size_t nmemb, size_t size)
{
	void *p; 
	p = calloc(nmemb, size);
	if(p == NULL)
		i_die("Can't calloc.\n");
	return p;
}

static void *erealloc(void *ptr, size_t size)
{
	void *p; 
	p = realloc(ptr, size);
	if(p == NULL)
		i_die("Can't realloc.\n"); 
	return p;
}

void f_delete(void)
{ 
	Filepos pos0 = fcur;
	Filepos pos1 = (Filepos)m_prevchar(fcur);
	
	i_sortpos(&pos0, &pos1);
	
	if(i_deltext(pos0, pos1)) 
		fcur = pos0;
	else
		fcur = fsel = pos0;
}

void f_insert(void)
{
	Filepos newcur;
	newcur = i_addtext((char *) c, fcur);
	if(fcur.l != newcur.l)
		fsel = newcur;

	fcur = fsel = newcur; 
} 


/* Add text at pos, return the position after the inserted text */
Filepos i_addtext(char *buf, Filepos pos)
{
	Line *l = pos.l, *lnew = NULL; 
	size_t o = pos.o, i = 0, il = 0;
	Filepos f;
	char c; 
	
	for(c = buf[0]; c != '\0'; c = buf[++i]) { 
		/* newline / line feed */
		if(c == '\n' || c == '\r') {
			lnew = (Line *)ecalloc(1, sizeof(Line));
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

/* Update the vlen value of a Line */
void i_calcvlen(Line * l)
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
bool i_deltext(Filepos pos0, Filepos pos1)
{
	Line *ldel = NULL; 
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
		edfastgetch();
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
	Line *l = NULL; 
	
	ansiinit();
	normalizetoscr();
	ansicreate();
	/* Init line structure */
	l = (Line *) ecalloc(1, sizeof(Line));
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
void i_sortpos(Filepos * pos0, Filepos * pos1)
{
	Filepos p;

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
	Line *l;
	
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
					if ( regexon == 1)
						highlight(l->c, ichar, lim);
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
	Line *l; 

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

Filepos m_bol(Filepos pos) {
	pos.o = 0;
	return pos;
}

Filepos m_nextchar(Filepos pos) {
	if(pos.o < pos.l->len) {
		pos.o++; 
	} else if(pos.l->next) {
		pos.l = pos.l->next;
		pos.o = 0;
	}
	return pos;
} 

Filepos m_prevchar(Filepos pos) {
	if(pos.o > 0) {
		pos.o--; 
	} else if(pos.l->prev) {
		pos.l = pos.l->prev;
		pos.o = pos.l->len;
	}
	return pos;
} 

Filepos m_nextline(Filepos pos) {
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

Filepos m_prevline(Filepos pos) {
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

Filepos m_nextscr(Filepos pos) {
	int i;
	Line *l; 
	for(i = lines, l = pos.l; l->next && i > 0; i -= VLINES(l), l = l->next)
		;
	pos.l = l;
	pos.o = pos.l->len;
	return pos;
} 

Filepos m_prevscr(Filepos pos) {
	int i;
	Line *l; 
	for(i = lines, l = pos.l; l->prev && i > 0; i -= VLINES(l), l = l->prev)
		;
	pos.l = l;
	pos.o = 0;
	return pos;
} 

size_t edfastgetch(void)
{
	static size_t len = 0; 
	  
	ch = fastgetch(); 

	switch (ch) { 
	case K_ESCAPE: 
		ch = fastgetch(); 
		switch (ch) {
			case '[': 
				ch = fastgetch(); 
				switch (ch) { 
					case 'A': /* arrow up */ 
						fcur = (Filepos)m_prevline(fcur); 
						break;
					case 'B': /* arrow down */ 
						fcur = (Filepos)m_nextline(fcur); 
						break;
					case 'C': /* right arrow */ 
						fcur = (Filepos)m_nextchar(fcur); 
						break;
					case 'D': /* left arrow */ 
						fcur = (Filepos)m_prevchar(fcur); 
						break;
					case 'H': /* Home */ 
						fcur = (Filepos)m_bol(fcur);
						ch = fastgetch(); 
						break;
					case '5': /* page up */ 
						fcur = (Filepos)m_prevscr(fcur);
						ch = fastgetch(); 
						break; 
					case '6': /* page down */ 
						fcur = (Filepos)m_nextscr(fcur);
						ch = fastgetch(); 
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

void highlight(char *s, int i, size_t lim)
{ 
	size_t j = 0, k;
	static int inacomment = 0;
	
	if ( s[i] == '/' && s[i + 1] == '*') 
		inacomment = 1;

	if ( s[i] == '*' && s[i + 1] == '/') 
	{
		hardadd = 1;
                addcolor(T_BLUE_FG,T_BLUE_FG_SZ, lim);
		addcolor(T_BLUE_FG,T_BLUE_FG_SZ, lim + 1);
                hardadd = 0;
		if ( inacomment == 0 ) 
		{
			hardadd = 1;
			for (j = lim; j > 0; --j)
                	       addcolor(T_BLUE_FG, T_BLUE_FG_SZ, j); 
			hardadd = 0;
		} 
		inacomment = 0;
	}
	
	if ( inacomment == 1 )
	{
		hardadd = 1;
		addcolor(T_BLUE_FG,T_BLUE_FG_SZ, lim);
		hardadd = 0; 
	}
	
	for ( k = 0; k < TOTMAPS ;) 
	{
		if (((regexec(&re[k], s+ i, 2, rm[k], 0)) == 0)) 
		{
       			for (j = rm[k][0].rm_so; j < (unsigned int)rm[k][0].rm_eo ; ++j)
				addcolor(COLORS[k], T_BLUE_FG_SZ, lim + j); 
		
		}
		++k;
	}
}

