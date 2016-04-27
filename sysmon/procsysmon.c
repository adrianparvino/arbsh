#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <signal.h> 
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h> 
#include <ctype.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <errno.h>
#include <stdint.h>

/* local librarie */
#include "../clib/ansicode.h"
#include "../clib/date.h"

/* defines */ 
#define BUF_MAX 1024
#define MAX_CPU 128
#define DATEFMT "%y/%m/%d %H:%M:%S"
#define VERBOSE 0
#define TICKS 1
#define INIT_PROCS 50
#define THREAD_MULT 4
#define MAX_LINE 256
#define INTERVAL 2 
#define SANITYLIMIT 100000

/* structs */ 
struct proc_info { 
	char *pid; /* convert to a pid_t at kill time */ 
	char *name;
	char state; 
} proc_info;

static struct proc_info new_procs[1000][100]; 
//static struct proc_info *new_procs[1000];


/* globals */
size_t bufcount =0;
char bufferp[1000][1000]; 
DIR *proc_dir; 
size_t max_procs;
size_t num_old_procs, num_new_procs;
size_t num_used_procs;
int pass = 0; 
size_t limiter = 0;
size_t limitoff = 0;

/* user control globals */
int metercpu = 1;
int meterloadavg = 1;
int meteruptime = 1;
int meterdate = 1;
int meterhost = 1;
int meterfinishbar = 1;
int meterprocs = 1;
int meternumbercpu = 1;
int meterswap = 1;
int meterram = 1;

/* functions */
void print_procs(void);
static void read_procs(void);
void read_stat(char *, struct proc_info *);
void findprocs(void); 
/* misc orig */
size_t allbars = 0; 
int winchg = 1;

struct proctlines {
	char *buf;
	char *fields[10000];
	size_t c;
} proctlines = { NULL, {}, 0};

static struct proct {
	struct proctlines lines[1000];
	size_t total;
}proct = {{}, 0};

int parseproc (void);
int proc_stat(char *);
void beautifulbars(size_t, double);
void mongetch(void);

static void sigwinch(int sig)
{
	if (sig)
		winchg = 1;
} 

int main()
{
	signal(SIGWINCH, sigwinch);
	parseproc();
	return 0;
}
int cols;
int parseproc (void)
{ 
	static size_t f[10] = { 0 };
	size_t tick[MAX_CPU] = { 0 };
	size_t tick_old[MAX_CPU] = { 0 };
	size_t idle[MAX_CPU] = { 0 };
	size_t idle_old[MAX_CPU] = { 0 };
	size_t del_tick[MAX_CPU] = { 0 };
	size_t del_idle[MAX_CPU] = { 0 };
	int i, j, k;
	int count;
	double percent;
	size_t num0, num1, num2, num3, ram;
	size_t len;
	
	char temp[BUFSIZ]; 
	size_t length = 0; 
	int ret = 0; 
	fd_set rfs; 

	/* create some windows */
	for ( i = 0 ; i < 10 ; ++i)
	{
		ansiinit();
		ansicreate(); 
	} 
	
	/* divide the screen */
	cols = (ansiglb.col / 2 ); 

	termcatch(~(ICANON | ECHO), 0);

	hardadd = 1;
	
	while (1)
	{ 
		
		/* MAKE SURE TO RESET BUFCOUT !! */ 
		bufcount = 0;
		
		dothink = 0;
		if ( winchg == 1)
		{ 
			ansiinit();
			cols = (ansiglb.col / 2 );
			dothink = 1;
			winchg = 0;
		}
		
		/* Catch keyboard events */
		FD_ZERO(&rfs);
		FD_SET(0, &rfs);	
		struct timeval t = { INTERVAL, 0}; 
		
		if ((ret = select(1, &rfs, 0, 0, &t) ) < 0 )
		{
			if (errno == EINTR)
				continue;
			write(1, "Select failed.\n", 16);
		} 

		if (FD_ISSET(0, &rfs))
		{ 
			mongetch();
			FD_ZERO(&rfs); 
			goto drawprocs;
		}
	
		/* /proc/stat */
		write(1, T_YELLOW_FG, T_YELLOW_FG_SZ);
		proc_stat("/proc/stat");
		allbars = 0;
		memset(f, 0, 10);

		/* CPU */
		ansiglb.c = 0;
		for ( percent = len = count = 0; metercpu ; count++)
		{ 
			tick_old[count] = tick[count];
			idle_old[count] = idle[count]; 
			if ( strcmp("intr", proct.lines[count].fields[0]) == 0 ) 
				break; 
			for (i=0, tick[count] = 0; i<10; i++) 
				tick[count] += atoi(proct.lines[count].fields[i + 1]);
			idle[count] = atoi(proct.lines[count].fields[3 + 1]);
			del_tick[count] = tick[count] - tick_old[count];
			del_idle[count] = idle[count] - idle_old[count]; 
			percent = ((del_tick[count] - del_idle[count]) / (double) del_tick[count]) * 100;
			beautifulbars(cols, percent); 
		} 

		/* /proc/meminfo */
		if ( meterram )
		{
			proc_stat("/proc/meminfo"); 
			percent = len = 0;
			num0 = atoi(proct.lines[0].fields[1]) / 1024;
			num1 = atoi(proct.lines[1].fields[1]) / 1024;
			num2 = atoi(proct.lines[2].fields[1]) / 1024;
			num3 = atoi(proct.lines[3].fields[1]) / 1024;
			ram = (num0) - ((num1)+(num2)+(num3));
			(void)ram;
			percent = ((num1)+(num2)+(num3)) / (double)(num0) * 100;
			percent = ( 100 - percent ); 
			beautifulbars(cols, percent);
		}

		
		if ( meterswap )
		{
			percent = len = 0;
			num0 = atoi(proct.lines[13].fields[1]) / 1024;
			num1 = atoi(proct.lines[14].fields[1]) / 1024;
			percent = (num1) / (double)(num0) * 100;
			percent = ( 100 - percent ); 
			beautifulbars(cols, percent);
		}

		/* DRAW THE BARS */ 
		int baroff = 5;
		ansiredraw((allbars), 1, baroff, ansiglb.col - cols - baroff); 
		
		if ( meternumbercpu )
		{
			i = percent = len = 0;
			ansiglb.c = 1;
			k = count;
			addcolorrange(T_CYAN_FG, T_BLUE_FG_SZ, len, len +4);
			len += ansiaddmem("Avg ", len, len + 4);
			while ((i+1) < k )
			{ 
				j = sprintf(temp, "%-4d", i);
				addcolorrange(T_CYAN_FG, T_BLUE_FG_SZ, len, len +j);
				len += ansiaddmem(temp, len, len + j); 
				++i;
			}
			addcolorrange(T_CYAN_FG, T_BLUE_FG_SZ, len, len +4);
			len += ansiaddmem("Mem ", len, len + 4);
			addcolorrange(T_CYAN_FG, T_BLUE_FG_SZ, len, len +4);
			len += ansiaddmem("Swp ", len, len + 4); 
			write(1, T_GREEN_FG, T_GREEN_FG_SZ); 
			ansiredraw(len, 1, 1, ansiglb.col - baroff ); 
		}
		
		if ( meteruptime )
		{
			size_t z = 0;
			ansiglb.c = 2; 
			proc_stat("/proc/uptime");
			i = percent = len = 0; 
			i = atoi(proct.lines[0].fields[0]);
			length = sprintf(temp, "Uptime ");
			z = length;
			addcolorrange(T_CYAN_FG, T_CYAN_FG_SZ, 0,  length);
			length += sprintf(temp + length, "%d", i / 60 / 60 / 24);
			length += sprintf(temp + length, ":%d", i / 60 / 60 % 24);
			length += sprintf(temp + length, ":%d", i / 60 % 60); 
			addcolorrange(T_BLUE_FG, T_BLUE_FG_SZ, z, length);
			len += ansiaddmem(temp, len, len + length);
			ansiredraw(len, 2, ansiglb.col - cols + 4 + baroff, 0);
		} 
		
		if ( meterloadavg )
		{
			ansiglb.c = 3; 
			i = percent = len = 0;
			proc_stat("/proc/loadavg"); 
			len += ansiaddstr("Loadavg ", len); 
			i = len;
			addcolorrange(T_CYAN_FG, T_CYAN_FG_SZ, 0, len);
			len += ansiaddstr(proct.lines[0].fields[0], len); 
			len += ansiaddstr(" ", len); 
			len += ansiaddstr(proct.lines[0].fields[1], len); 
			len += ansiaddstr(" ", len); 
			len += ansiaddstr(proct.lines[0].fields[2], len);
			addcolorrange(T_BLUE_FG, T_BLUE_FG_SZ, i, len);
			ansiredraw(len, 3, ansiglb.col - cols + 4 + baroff, 0);	
		} 
		
		if ( meterdate )
		{
			ansiglb.c = 4;
			i = percent = len = 0;
			i = date(temp, DATEFMT, 100);
			addcolorrange(T_CYAN_FG, T_CYAN_FG_SZ, 0, 5);
			len += ansiaddmem("Time ", 0, 5);
			len += ansiaddmem(temp, len, len + i);
			addcolorrange(T_BLUE_FG, T_BLUE_FG_SZ, 5, len + i);
			ansiredraw(len, 4, ansiglb.col - cols + 4 + baroff, 0);
		} 
		
		if ( meterhost )
		{ 
			i = percent = len = 0;
			gethostname(temp, 100);
			ansiglb.c = 5;
			addcolorrange(T_CYAN_FG, T_CYAN_FG_SZ, 0, 5);
			len += ansiaddmem("Host ", 0, 5);
			len += ansiaddmem(temp, len, len + strlen(temp));
			addcolorrange(T_BLUE_FG, T_BLUE_FG_SZ, 5, len);
			ansiredraw(len, 5, ansiglb.col - cols + 4 + baroff, 0); 
		} 
		
		if ( meterfinishbar )
		{
			ansiglb.c = 6;
			write(1, T_BLACK_FG, T_BLACK_FG_SZ);
			write(1, T_GREEN_BG, T_GREEN_BG_SZ);
			i = percent = len = 0;
			
			len += ansiaddmem("PID CPU% S #THR VSS RSS UID", 0, 27);
			len += ansiaddmem(WHITESPACE, len, ansiglb.col); 
			addcolorrange(T_BLACK_FG, T_BLACK_FG_SZ, 0, len);
			ansiredraw(len, allbars / (cols) + 1, 0, 0); 
		} 
		
		drawprocs:
		if ( meterprocs )
		{
			write(1, T_BLACK_BG, T_BLACK_BG_SZ); 
			write(1, T_CYAN_FG, T_CYAN_FG_SZ);
			setcursor(allbars / (cols) + 2 , 1); 
			limiter = (ansiglb.row - (allbars / (cols) + 2 + 1)); 
			setcursor(allbars / (cols) + 2 + 1, 1);
			findprocs(); 
		}
	}
 
	return 0;
} 

void beautifulbars(size_t cols, double percent)
{ 
	size_t bar = 0;
	int off = 2; 

	ansiwaddch('[', allbars++);
	for (; bar < (cols - off) ; ++bar)
	{
		if ( bar < percent)
		{
			ansiwaddch('|', allbars);
			if ( bar <  (percent / 4))
				addcolor(T_GREEN_FG,T_GREEN_FG_SZ, allbars);
			else if ( bar < (percent / 2 ))
				addcolor(T_YELLOW_FG,T_YELLOW_FG_SZ, allbars);
			else
				addcolor(T_RED_FG,T_RED_FG_SZ, allbars);
			allbars++; 
		}
		else {
			ansiwaddch(' ', allbars++); 
			//addcolor(T_BLUE_FG,T_YELLOW_FG_SZ, lim);
		}
	} 
	
	ansiwaddch(']', allbars++);
} 

int proc_stat(char *file)
{
	int fd;
	size_t len, i, j, k;
	char *token = NULL;
	
	i = j = k = len = fd = 0; 
	proct.total = 0; 

	if ( bufcount >= SANITYLIMIT )
		bufcount = SANITYLIMIT;

	if ((fd = open(file, 0)) == -1) 
		return -1;
	if ((len = read(fd, bufferp[bufcount], BUFSIZ)) < 1) 
		return -1;
	
	bufferp[bufcount][len] = '\0';
	

	close(fd);
	token = strtok(bufferp[bufcount], "\n");
	while ( token != NULL )
	{
		proct.lines[proct.total].buf = token;
		token = strtok(NULL, "\n");
		proct.total += 1;
	} 
	while ( j < proct.total )
	{ 
		token = strtok(proct.lines[j].buf , " ");
		proct.lines[j].fields[0] = token;
		k = 0;
		proct.lines[j].c = 0;
		while ( token != NULL )
		{ 
			proct.lines[j].fields[k] = token;
			token = strtok(NULL, " ");
			++k;
			proct.lines[j].c += 1;
		}
		++j;
	} 
	for ( i = j = k = 0; VERBOSE && i < proct.total ; ++i) /* verbosity */
		for (k = 0; k < proct.lines[i].c ;k++) 
			write(1, proct.lines[i].fields[k], strlen(proct.lines[i].fields[k]));
	++bufcount;
	return 0;
}

void mongetch(void)
{ 
	int ch = 0; 
	ch = ansigetch(); 
	switch (ch) { 
	case K_ESCAPE:
		ch = ansigetch(); 
		switch (ch) {
		case '[':
			ch = ansigetch(); 
			switch (ch) {
			case 'A': /* arrow up */ 
				ch = ansigetch();
				if (limitoff > 0)
					--limitoff;
				break;
			case 'B': /* arrow down */ 
				ch = ansigetch();
				if (limitoff < (1000))
					++limitoff;
				break; 
		       }
		}
		return;
	case 'q':
		termcatch(~(ICANON | ECHO), 1);
		exit(0);
		break; 
	default: 
		break;
	}
	return;
}

void findprocs()
{ 
	num_used_procs =  0; 
	max_procs = 0; 
	read_procs(); 
	print_procs(); 
	closedir(proc_dir);
} 

static void read_procs(void)
{ 
	struct dirent *dir;
//	char *filename[1000];
	int i; 
	
	proc_dir = opendir("/proc");
	num_new_procs = INIT_PROCS;
	proc_stat("/proc/stat");

	for(i = 0;(dir = readdir(proc_dir));)
	{
		if (!isdigit(dir->d_name[0]))
			continue; 
		new_procs[i]->pid = dir->d_name; 
		if (chdir("/proc/") != 0)
			return;
		if (chdir(dir->d_name) != 0)
			return; 
		proc_stat("stat");
		//strcpy(new_procs[i]->name, proct.lines[0].fields[1]); 
		new_procs[i]->name = proct.lines[0].fields[1];
		new_procs[i]->state = proct.lines[0].fields[2][0];
		num_new_procs = i; 
		++i;
	} 

	//closedir(proc_dir);
} 

void print_procs(void)
{
	size_t i = 0;
	size_t j, buflen, last; 
	char buffer[100000]; 

	last = buflen = 0;

	for (i = 0; i < num_new_procs && i < SANITYLIMIT; i++)
	{ 
		if ( i >= (limiter + limitoff))
			break;
	
		if (!new_procs[i] || (max_procs && (i >= max_procs)))
			break;
   
		buflen += sprintf(buffer + buflen, "%s  ", new_procs[i]->pid); 
		buflen += sprintf(buffer + buflen, "%c  ", new_procs[i]->state); 
		buflen += sprintf(buffer + buflen, "%s ", new_procs[i]->name);
		for (j = (buflen - last); j < ansiglb.col ; ++j, ++buflen) 
			buffer[buflen] = ' '; 
		last = buflen; 
	} 
	
	ansihorizon(allbars / (cols) + 2 + 1, ansiglb.row);
	setcursor(allbars / (cols) + 2 + 1, 1);
	write(1, T_CLRCUR2BOT, T_CLRCUR2BOT_SZ);
	write(1, buffer, buflen); 
}

