#include <unistd.h> 
#include <sys/socket.h> 
#include <sys/ioctl.h> 
#include <arpa/inet.h> 
#include <sys/select.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <termios.h>
#include <time.h>
#include <signal.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

/* local libraries */ 
#include "../clib/string.h"
#include "../clib/ansicode.h"
#include "../clib/dial.h"
#include "../clib/ircline.h"
#include "../clib/date.h"

/* 
        2015 (C) Copyright, `Irc', CM Graff MIT/BSD Licensed 
        See LICENSE for copying details.
*/

/* ANSI escape sequences (see ansicode.h) */
#define USERCOLOR 	T_BOLD
#define OTHERUSERS	T_BLUE_FG T_BOLD
#define BARCOLOR	T_BLUE_BG

/* trivial compile time limits and defines */
#define INTERVAL 100000
#define CHANLEN 	64
#define LINELEN 	512
#define MAXCHANS 	100
#define DATEFMT 	"%H:%M"
#define ID_DELAY	100000


/* structs */
struct chan {
	char *name;
	char *buf;
	char *eol;
	size_t scroll;
	size_t scrolls;
	size_t sz;   	/* size of buffer in memory */
	size_t real; 	/* size of buffer's printable text */
} *chl;

struct servstrct {
	struct chan chl[10];
	char *server;
	char *line;
	char *p;
	int ch;         /* current channel */
	int nch;        /* total channels */ 
} ss[10];

/* These stay the same regardless of the server */
struct glb {
	char userline[BUFSIZ];
	char *nick;
	size_t nicklen;
	size_t w; 	/* terminal dimensions */
	size_t h;
	int runstate;
} glb = { {}, NULL, 0, 0, 0, 1};

/* globals */ 
unsigned short port = 0;
int sck[100];
int sckno = 0;
int winchg = 0;
size_t curserv = 0;
size_t numserv = 0;
char *server;
char *channel = NULL;
char *identify = NULL;
fd_set rfs;

/* function prototypes */
void accumulator(int, char *, char *, char *);
int chadd(char *);
int chdel(char *);
int chfind(char *);
int delconn(char *s);
void detectmessage(char *, char *, char *, char *);
void drawscreen(void);
size_t ircgetch(char *); 
void panic(const char *);
void printout(void); 
int readin(void);
int setupconn(char *, int);
static void sigwinch(int);
void uparse(char *);


int main(int argc, char *argv[])
{ 
        char *tok;
        char *postok; 
	int ret;
	size_t len = 0;
	size_t z = 0; 
	
	sck[sckno] = -1; 

        if ( argc > 1 && strcmp(argv[1], "-h") == 0)
        {
		write(2, argv[0], strlen(argv[0])); 
		write(2, " server=irc.freenode.net port=6667", 34);
		write(2, " nick=doormouse channel='#irctest'\n", 35);
                return 0;
        }
	
	if (!(glb.nick = malloc(sizeof(char) *BUFSIZ)))
                return 1;
	gmemset(glb.nick, 0, BUFSIZ);
	strcpy(glb.nick, "None");
       
        while ( *argv )
        {
                tok = strtok(*argv, "=");
                postok = strtok(NULL, "=");
                if ( strcmp(tok, "server") == 0 )
                        server = postok;
                else if ( strcmp(tok, "port") == 0 )
                        port = atoi(postok);
                else if ( strcmp(tok, "nick") == 0 )
			strcpy(glb.nick, postok);
                else if ( strcmp(tok, "channel") == 0 )
                        channel = postok;
                else if ( strcmp(tok, "identify") == 0 )
                        identify = postok;
                ++argv;
        }

	termcatch(~(ICANON | ECHO), 0);
	
	if ( server && port && glb.nick )
	{
		setupconn(server, port);
		if ( channel ) 
			chadd(channel); 
		
	} else if ( sck[sckno] == -1 )
	{
		chadd("blank");
		accumulator(0, "%s" "%s\t" "%s", "", "You are not connected to a server.");
		accumulator(0, "%s" "%s\t\t" "%s", "", "Examples:");
		accumulator(0, "%s" "%s\t\t" "%s", "", "/c irc.freenode.net 6667");
		accumulator(0, "%s" "%s\t\t" "%s", "", "/j #irctest");
		accumulator(0, "%s" "%s\t\t" "%s", "", "/n newnick\n");
		accumulator(0, "%s" "%s\t\t" "%s", "", "Key binds:");
		accumulator(0, "%s" "%s\t\t" "%s", "", "ctrl-n\tChange channels");
		accumulator(0, "%s" "%s\t\t" "%s", "", "ctrl-x\tChange server");
	} 
	
        signal(SIGWINCH, sigwinch); 
	determinewin();
        glb.w = hglb.w = win.ws_col;
        glb.h = hglb.h = win.ws_row; 
	
	
	while ( glb.runstate )
	{ 
		if ( winchg == 1)
		{ 
			determinewin(); 
			glb.w = hglb.w = win.ws_col;
			glb.h = hglb.h = win.ws_row;
			drawscreen();
			winchg = 0; 
		}
		
		/* handle non-connective cases */
		if ( numserv == 0 )
		{
			drawscreen();
			glb.w = hglb.w = win.ws_col;
        		glb.h = hglb.h = win.ws_row;
			gshprint(glb.userline, len, "[[ ]]>> ", 8);
			len = ircgetch(glb.userline);
			continue;
		} 
		
		FD_SET(0, &rfs); 
			
		for ( z=0; z < numserv; ++z)
                { 
			FD_SET(sck[z], &rfs); 
			
			/* determine whether to catch keys or listen to the socket */ 
			struct timeval t = { 0, INTERVAL};
			
			if ((ret = select(sck[z] + 1, &rfs, 0, 0, &t) ) < 0 )
			{
				if (errno == EINTR)
					continue;
				panic("Select failed.");
			} 
               
			/* Listen to the socket */
			if (FD_ISSET(sck[z], &rfs))
			{ 
				sckno = z;
				readin(); 
				drawscreen();
				gshprint(glb.userline, len, "[[ ]]>> ", 8); 
				sckno = curserv;
			} 
		}

		/* Catch keyboard events */ 
		if (FD_ISSET(0, &rfs))
                { 
               	        sckno = curserv; 
               		determinewin();
                       	glb.w = hglb.w = win.ws_col;
                       	glb.h = hglb.h = win.ws_row;
                       	len = ircgetch(glb.userline);
                       	gshprint(glb.userline, len, "[[ ]]>> ", 8);
               	}
		
	}
	
	
	/* reset terminal */
	termcatch(~(ICANON | ECHO), 1);

	/* TODO: close sockets and free memory */

        return 0; 
}

int chadd(char *name)
{
        //if (ss[i].nch > 0 && !(ss[i].chl = realloc (ss[i].chl, sizeof(chl) * (ss[i].nch + 1))))
        //      panic("Out of memory 2.");
        size_t i = sckno;

        if (!(ss[i].chl[ss[i].nch].name = malloc(sizeof(char) *BUFSIZ)))
                panic("Out of memory 3.");
        gmemset(ss[i].chl[ss[i].nch].name, 0, BUFSIZ);
        strcpy(ss[i].chl[ss[i].nch].name, name);
        ss[i].chl[ss[i].nch].sz = BUFSIZ;
        if (!(ss[i].chl[ss[i].nch].buf = malloc(sizeof(char) * BUFSIZ)))
                panic("Out of memory 4.");
        gmemset(ss[i].chl[ss[i].nch].buf, 0, BUFSIZ);


        ss[i].chl[ss[i].nch].eol = ss[i].chl[ss[i].nch].buf;
        ss[i].chl[ss[i].nch].scroll = 0;
        ss[i].chl[ss[i].nch].scrolls = 0;
        ss[i].chl[ss[i].nch].real = 0;
        ss[i].ch = ss[i].nch++;

        write(sck[i], "JOIN ", 5);
        write(sck[i], name, strlen(name));
        write(sck[i], "\r\n", 2);

        return ss[i].nch;
} 

int chfind(char *name)
{
	size_t i = 0;

	for (i = ss[sckno].nch - 1; i > 0; i--)
		if (!strcmp(ss[sckno].chl[i].name, name))
			break;
	return i;
} 

void detectmessage(char *usr, char *cmd, char *par, char *data)
{ 
	/*
		Detect_message() inspects server messages for information
		pertaining to which channel they are intended to be displayed
		on and then passes them to the appropriately numbered channel
		for the data to be accumulated by 'accumulator()'.
	*/ 
	char *pm;
	char *store = par;
	//if ( *par )
	if ( !(pm = strtok(par, " ") ))
		pm = store;
 
	//char *pm = par;

	if (!strcmp(cmd, "PRIVMSG")) 
	{ 
		/* respond to VERSION requests, a hack */
		if ( strcmp(data, "\001VERSION\001") == 0 )
		{
			write(sck[sckno], "NOTICE ", 7);
			write(sck[sckno], usr, strlen(usr)); 
			write(sck[sckno], " :\001VERSION Irc in C by CM Graff\001\r\n", 33);
		} else
		{ 
			/* private message user channels */
			if ((strcmp(glb.nick, par)) == 0 )
			{
				strtok(usr, "!"); 
				if ( chfind(usr) == 0 ) 
					chadd(usr);
	
				accumulator(chfind(usr), "%s" OTHERUSERS "<%s>" T_CLRCHARS" %s", usr, data);
			}
			/* regular channels */
			else {
				accumulator(chfind(pm), "%s" OTHERUSERS "<%s>" T_CLRCHARS" %s", usr, data);
			}
			
		}
	}
	else if (!strcmp(cmd, "PING"))
		write(sck[sckno], "PONG :\r\n", 8); 
	else if (!strcmp(cmd, "PART"))
		accumulator(chfind(pm), "%s "T_CYAN_FG"%s <-- part"T_CLRCHARS, usr, "");
	else if (!strcmp(cmd, "JOIN"))
		accumulator(chfind(pm), "%s "T_CYAN_FG"%s --> join"T_CLRCHARS, usr, ""); 
	else if (!strcmp(cmd, "QUIT")) 
               	accumulator(0, "%s "T_GREEN_FG"%s <-- %s"T_CLRCHARS, cmd, usr); 
	else if (!strcmp(cmd, "NOTICE"))
		accumulator(0, "%s """, data, "");
	else if (!strcmp(cmd, "375"))
		accumulator(0, "%s """, data, "");
	else if (!strcmp(cmd, "372"))
		accumulator(0, "%s ""%s", data, "");
	else if (!strcmp(cmd, "376"))
		accumulator(0, "%s ""%s", data, "");
	else if (!strcmp(cmd, "353"))
		accumulator(ss[sckno].nch - 1, "%s ""%s", data, "");
	else if (!strcmp(cmd, "366"))
		accumulator(ss[sckno].nch - 1, "%s ""%s", data, "");
	else if (!strcmp(cmd, "332"))
               	accumulator(ss[sckno].nch - 1, "%s ""%s", data, "");
	else if (!strcmp(cmd, "412"))
		accumulator(0, "%s ""%s ==> %s", cmd, data); 
	else if (!strcmp(cmd, "396")) 
                accumulator(0, "%s ""%s ++> %s", cmd, data);
	else if (!strcmp(cmd, "470")) 
		accumulator(0, "%s ""%s ##> %s", cmd, data); 
	else if (!strcmp(cmd, "NICK"))
                accumulator(0, "%s "T_YELLOW_FG"%s ------> %s"T_CLRCHARS, usr, data); 
	else if (!strcmp(cmd, "ERROR"))
	{
		accumulator(0, "%s "T_RED_FG"%s <XXXXX> %s"T_CLRCHARS, usr, data); 
		sck[sckno] = -1;
		--numserv;
		//--curserv;
		FD_ZERO(&rfs);
	}
	else {
		accumulator(0, "%s ""%s Not parsed by Irc. %s", cmd, data);
		accumulator(0, "%s" OTHERUSERS "<%s>" T_CLRCHARS" %s", usr, data);
	}
	
} 

void panic(const char *m)
{
	write(2, "Panic: ", 7);
	write(2, m, strlen(m));
	write(2, "\n", 1);
	glb.runstate = 0;
} 

int readin(void)
{
        static char l[BUFSIZ], *p=l;
        char *s, *usr, *cmd, *par, *data;
        int rd;

        if (p - l >= BUFSIZ) 
		p = l;
        
	rd = read(sck[sckno], p, BUFSIZ - (p-l));
	

        if (rd < 0)
	{
                if (errno == EINTR) 
			return -1;
                //panic("IO error while reading.");
		//return -1;
        }
        if (rd == 0) 
		return 0;
        p += rd;
	/* Cycle on all received lines. */
        for (;;)
	{ 
                if (!(s = memchr(l, '\n', p-l)))
                        return 1;
                if (s > l && s[-1] == '\r')
                        s[-1] = 0;
                *s++ = 0;
                if (*l == ':') {
                        if (!(cmd = strchr(l, ' '))) 
				goto lskip;
                        *cmd++ = 0;
                        usr = l + 1;
                } else {
                        usr = 0;
                        cmd = l;
                }
                if (!(par = strchr(cmd, ' '))) 
			goto lskip;
                *par++ = 0;
                if ((data = strchr(par, ':')))
                        *data++ = 0;
		detectmessage(usr, cmd, par, data);
                //scmd(usr, cmd, par, data);
        lskip:
                memmove(l, s, p-s);
                p -= s - l;
        }
}


void uparse(char *string)
{
        //if ( *string == '/' || sck[i] == -1 )
        size_t i = curserv;
        if ( *string == '/')
        {
                if ( *(string + 1) == 'j' )
                {
                        string += 2;
                        string = strtok(string, " ");
                        if ( string && *string == '#')
                                chadd(string);
                }
                else if ( *(string + 1) == 'p' )
                {
                        string += 2;
                        string = strtok(string, " ");
                        if ( string && *string == '#')
                                chdel(string);
                }
                else if ( *(string + 1) == 'c' )
                {
                        char *serv;
                        string += 2;
                        if ( string )
                                serv = strtok(string, " ");
                        if ( serv )
                                string = strtok(NULL, " ");
                        if ( string )
                                port = atoi(string);
                        setupconn(serv, port);
                }
                else if ( *(string + 1) == 'd' )
                {
                        string += 2;
                        string = strtok(string, " ");
                        if ( string)
                                delconn(string);
                } else if ( *(string + 1) == 'r' ) {
                        write(sck[i], (string + 2), strlen(string + 2));
                        write(sck[i], "\r\n", 2);
                } else if ( *(string + 1) == 'x' ) {
                        write(sck[i], "\001", 1);
                } else if ( *(string + 1) == 'y' ) {
                        write(sck[i], "\r\n", 2);
                } else if ( *(string + 1) == 'z' ) {
                        write(sck[i], (string + 2), strlen(string + 2));
                } else if ( *(string + 1) == 'n' ){
                        string += 2;
                        if ( string )
                                string = strtok(string, " ");
                        if ( string )
                                strcpy(glb.nick, string);
                        write(sck[i], "NICK ", 5);
                        write(sck[i], glb.nick, strlen(glb.nick));
                        write(sck[i], "\r\n", 2);
                } else if ( *(string + 1) == 'q' )
                        glb.runstate = 0;
                return;
        }
        //string += mystrspn(string, " "); 
        accumulator(ss[i].ch, "%s " USERCOLOR "<%s> " T_CLRCHARS"%s", glb.nick, string);
        write(sck[i], "PRIVMSG ", 8);
        if ( ss[i].chl[ss[i].ch].name )
                write(sck[i], ss[i].chl[ss[i].ch].name, strlen(ss[i].chl[ss[i].ch].name));
        write(sck[i], " :", 2);
        if ( string )
                write(sck[i], string, strlen(string));
        write(sck[i], "\r\n", 2);
}




void accumulator(int cn, char *format, char *line1, char *line2)
{
	/*
		Aaccumulator() accumulates data for a channel and allocates
		any additional memory required for the buffer to hold it.
		This includes data from the user which is passed in via
		uparse(). It then passes this data to drawscreen() and 
		printout() to be displayed on the screen for the user.
	*/
	struct chan *const c = &ss[sckno].chl[cn];
	size_t n;
	size_t blen = c->eol - c->buf; 
	char buf[256];
	size_t i = 0;
	
	
	if ( (i = date(buf, DATEFMT, 100)) < 1)
	{
		strcpy(buf, "======"); /* in case date fails */
		i = 6;
	}

	if (blen + LINELEN + i >= c->sz) 
	{
		c->sz *= 2;
		if (! (c->buf = realloc(c->buf, c->sz)))
			panic("Out of memory.");
		c->eol = c->buf + blen;
	} 

	//n = snprintf(c->eol, LINELEN - 1 + i, format, buf, line1, line2); 
	n = sprintf(c->eol, format, buf, line1, line2);
	c->eol[n] = '\n';
	c->eol[n + 1] = '\0';
	c->eol += n + 1;
	c->real += (n + 1); 
} 

size_t ircgetch(char *l)
{
        static size_t len = 0;
        static size_t ret = 0;
        size_t z = 0;
        int c;

        c = supahfastgetch();

        switch (c) {
        case K_ESCAPE:
                c = supahfastgetch();
                switch (c) {
                case '[':
                        c = supahfastgetch();
                        switch (c) {
                        case 'A': /* arrow up */
                                if ( hglb.c > 0 )
                                {
                                        --hglb.c;
                                        strcpy(l, hist[hglb.c].line);
                                        len = hist[hglb.c].len;
                                        hglb.laro = 0;
                                }
                                break;
                        case 'B': /* arrow down */
                                if ( hglb.c < hglb.t )
                                {
                                        ++hglb.c;
                                        strcpy(l, hist[hglb.c].line);
                                        len = hist[hglb.c].len;
                                        hglb.laro = 0;
                                }
                                break;
                        case 'C': /* right arrow */
                                if ( hglb.laro > 0 )
                                        --hglb.laro;
                                break;
                        case 'D': /* left arrow */
                                if ( hglb.laro < len )
                                        ++hglb.laro;
                                break;
                        case 'H': /* Home */
                                hglb.laro = len;
                                break;
                        case '5': /* page up */ 
				c = supahfastgetch(); 
				if ( ss[sckno].chl[ss[sckno].ch].scroll < (ss[sckno].chl[ss[sckno].ch].real - (glb.w + glb.w)))
                                        ss[sckno].chl[ss[sckno].ch].scroll += glb.w;
				drawscreen();
                                break;
                        case '6': /* page down */
				c = supahfastgetch();
				if ( ss[sckno].chl[ss[sckno].ch].scroll > 0)
                                        ss[sckno].chl[ss[sckno].ch].scroll -= glb.w;
                                drawscreen();
                                break;
                        }
                }
                return len;
        case '\t':
                //write(1, "tab complete\n", 13);
                break;
	case K_CTRLENN :
		l[0] = '\0';
		len = 0;
		ss[sckno].ch = (ss[sckno].ch+1) % ss[sckno].nch;
                drawscreen();
                return 0;
	case K_CTRLEXX :
		if ( numserv > 0 )
			curserv = sckno = (sckno+1) % numserv;
		drawscreen();
		return 0;
        case '\n':
                write(1, "\n", 1);
                l[len] = '\0';
                ret = len;
                len = 0;
                hglb.r = 0;
                hglb.laro = 0;
                uparse(l);
		drawscreen();
		if ( ret > 0 )
			gsh_history(l, ret); 
                return 0;
		//return ret;
        case K_BACKSPACE:
                if ( len == 0 )
                        return len;
                if ( hglb.laro )
                {
                        z = (len - hglb.laro);
                        memmove(l + z - 1, l + z, hglb.laro);
                }

                l[--len] = '\0';

                return len;
        default:
                if ( hglb.laro )
                {
                        z = (len - hglb.laro);
                        memmove(l + z + 1, l + z, hglb.laro);
                        l[z] = c;
                }
                else {
                        l[len] = c;
                }

                l[++len] = '\0';

                break;
        }
        return len;
}
	
void drawscreen(void)
{

        size_t n = 0;

        size_t i = curserv;

        /* top bar */
        write(1, T_ERASEALL, T_ERASEALL_SZ);
        write(1, T_BLUE_BG, T_BLUE_FG_SZ);
        write(1, "\x1b[1;2r", 6);
        n = write(1, "[", 1);
        n += write(1, ss[i].chl[ss[i].ch].name, strlen(ss[i].chl[ss[i].ch].name));
        n += write(1, "] ", 2);

        n += write(1, "@ (", 3);
        n += write(1, ss[i].chl[0].name, strlen(ss[i].chl[0].name));
        n += write(1, ") ", 2);

        write(1, WHITESPACE, glb.w - n);
        write(1, T_BLACK_BG, T_BLACK_BG_SZ);
        write(1, "\n", 1);

        /* center text */
        write(1, "\x1b[2;", 4);
        writenumber(1, glb.h);
        write(1, "r\n", 2);
        write(1, T_ERASEBEGL2CUR, T_ERASEBEGL2CUR_SZ);

        /* Print only last 300 lines or so? (yes this sucks)*/
        size_t totalchars = hglb.w * hglb.h - ss[i].chl[ss[i].ch].scroll;

        if ( ss[i].chl[ss[i].ch].real > ( hglb.w * hglb.h ))
        {
                totalchars = ( hglb.w * hglb.h );
                write(1, ss[i].chl[ss[i].ch].buf + (ss[i].chl[ss[i].ch].real - totalchars) - ss[i].chl[ss[i].ch].scroll, totalchars);
        }
        else
                write(1, ss[i].chl[ss[i].ch].buf, ss[i].chl[ss[i].ch].real - ss[i].chl[ss[i].ch].scroll);

        /* bottom bar */
        write(1, T_BLUE_BG, T_BLUE_FG_SZ);
        n = 0;
        write(1, WHITESPACE, glb.w - n);
        write(1, T_BLACK_BG, T_BLACK_BG_SZ);
        write(1, "\n", 1);



        /* now the prompt can be drawn by another function */
}


void printout(void)
{ 
	write(1, glb.userline, strlen(glb.userline));
} 

int setupconn(char *s, int p)
{ 
	usleep(ID_DELAY);
	
	if (!glb.nick)
		return -1;

	if ((sck[numserv] = dialurl(s, p)) == -1) 
		return -1; 

	//ss = realloc(ss, sizeof (struct servstrct) * (numserv + 1)); 
	
	sckno = numserv;
	ss[numserv].nch = 0;
	chadd(s);

	//ss[numserv].nch = 1;

	glb.nicklen = strlen(glb.nick);
	write(sck[numserv], "NICK ", 5);
	write(sck[numserv], glb.nick, glb.nicklen);
	write(sck[numserv], "\r\n", 2);
	write(sck[numserv], "USER ", 5);
	write(sck[numserv], glb.nick, glb.nicklen);
	write(sck[numserv], " 8 * : \r\n", 9);
	write(sck[numserv], "MODE ", 5);
	write(sck[numserv], glb.nick, glb.nicklen);
	write(sck[numserv], " +i\r\n", 5);

	curserv = sckno = numserv;
	++numserv;
	
	return 0; 
}

int delconn(char *name)
{
	size_t i = 0;
	for (i = numserv - 1;i > 0 ;--i)
	{
		if ( strcmp(ss[i].chl[0].name, name) == 0 )
		{
			write(sck[i], "QUIT ", 5);
                        write(sck[i], name, strlen(name));
                        write(sck[i], "\r\n", 2);
			ss[i] = ss[numserv - 1];
			--numserv;
			return 0;
		}
	}
	return -1;
} 

int chdel(char *name)
{
	size_t i = 0;

        for (i = ss[sckno].nch - 1; i > 0; i--)
	{
                if (!strcmp(ss[sckno].chl[i].name, name))
		{ 
			ss[sckno].ch = 0;
			write(sck[sckno], "PART ", 5);
			write(sck[sckno], name, strlen(name));
			write(sck[sckno], "\r\n", 2);
			ss[sckno].chl[i] = ss[sckno].chl[ss[sckno].nch - 1];
			ss[sckno].nch -= 1;
                        return 0;
		}
	}
	return -1;
}

static void sigwinch(int sig)
{
        if (sig) 
		winchg = 1;
}

