#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* stat() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h> 
#include <limits.h> 

/* waitpid() */
#include <sys/wait.h>

/* greadline() */
#include <sys/ioctl.h>
#include <termios.h>
#include <stdint.h>
#include <readline/readline.h>

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct glb
{ 
	size_t count;	/* num of commands */
	size_t len;	/* input array len */
	int inascript;	/* script mode 	*/
	int testparse;	/* -t mode 	*/
	int cmode;	/* -c mode 	*/
}glb = { 0, 0, 0, 0, 0};


typedef struct{
	char *cmd[3];	/* command vector */
	int in;		/* stdin */
	int out;	/* stdout */
	pid_t pids;	/* for waitpid */
	int err;	/* for waitpid */
	int piped;	/* boolean value */
	char *infp;
	char *outfp;
	int outflags;
	int boole;
} object; 

object *piped(object *o)
{
	int fildes[2];
	if ((pipe(fildes)) == -1)
		return NULL;
	(o+1)->in = fildes[0];
	o->out = fildes[1];
	return o;
}

object *child(object *o)
{
	dup2(o->in, STDIN_FILENO);
	dup2(o->out, STDOUT_FILENO);
	execvp(o->cmd[0], o->cmd);
	_exit(1);
	return o;
}
object *foreground(object *o)
{
	waitpid(o->pids, &(o->err), 0);
	if (o->out != -1)
		close(o->out);
	if (o->in != -1)
		close(o->in);
	return o;
}

object *execute(object *o)
{ 
	if ( o->infp != NULL )			/* < */
	        if((o->in = open(o->infp, O_RDONLY)) == -1)
			return NULL;
	if (o->outfp != NULL )			/* >, >> */
	        if((o->out = open(o->outfp, o->outflags, 0755)) == -1)
			return NULL;
	if (o->piped == 1)			/* | */
	      	if(!(o = piped(o)))
			return NULL;
	if ((o->pids = fork()) == 0) 
		o = child(o);
	o = foreground(o);
	return o;
}

int main(void)
{
	size_t i = 0;
	object p[10] = {{{ "ls", "-l", NULL}, -1, -1, 0, 0, 1,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 0 ,NULL, "outfile", O_APPEND|O_RDWR|O_CREAT, -1}};

	object *o = p;

	for (;i<10;o++,++i)
	{
       	 	if (i && (o-1)->err == 0 && (o-1)->boole == 1)	/* || */
	      	        continue; 
	        if (i && (o-1)->err != 0 && (o-1)->boole == 0)	/* && */
	                continue;
		o = execute(o);
	}
	
	return 0;
} 
struct commands
{
	/* commands */
	char *argv[1024]; 
	size_t argc;
	/* io */
	char *outfp;
	char *infp;
	int outflags;
	int in;
	int out;
	/* pipes */
	int piped;
	/* processes */
	pid_t pids;
	int bg;
	int err;
	/* logic */
	int boole;	/* controlled by the preceding command */ 
} *cmds;

/* functions */

void verbosity(void)
{
        size_t i = 0;
        size_t j = 0;

	fprintf(stderr, "Total command vectors: %zu \n",glb.count);
        
        for (i = 0; i < glb.count ;i++)
        {
		fprintf(stderr, "\n");
		
                for ( j = 0; j <= cmds[i].argc ; ++j) 
                        fprintf(stderr, "%s\t\targv           %zu\n", cmds[i].argv[j], j); 
                if ( cmds[i].infp != NULL )
                        fprintf(stderr, "%s\t\tin  <   vector %zu\n", cmds[i].infp, i);
                if ( cmds[i].outfp != NULL ) 
                        fprintf(stderr, "%s\t\tout >   vector %zu\n", cmds[i].outfp, i); 
        }
	if ( glb.inascript)
		exit(1);
}

static void initialize(size_t i)
{
        if (!(cmds = realloc(cmds, sizeof(struct commands) * (i + 1))))
	{
		perror(" realloc()" );
		exit(1);
	}

	cmds[i].argv[0] = NULL;
	cmds[i].argc = 0; 

	cmds[i].outflags = O_APPEND|O_RDWR|O_CREAT;
        cmds[i].outfp = NULL;
        cmds[i].infp = NULL;
        cmds[i].in = -1;
        cmds[i].out = -1;
        
        cmds[i].bg = 0;
        cmds[i].piped = 0;
        cmds[i].err = 0;
        cmds[i].boole = -1;
}

int parse(char *l)
{
	/* grammar */
	int atoken = 0;
	int awhite = 1;
	int aredir = 0;
	int aquote = 0; 
	/* total commands */
	size_t c = 0;
	
	/* remain at the start of a command sequence */
	char *last;
	
	/* intialialize a data structure member and the pointer to input */
	initialize(c);
        last = l;

	/* discover tokens and commands */
        while ( *l )
        { 
		if (*l == ';')
                {
                        *l = '\0';
                        initialize(++c);
                        last = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
		else if (*l == '\n' && *(l + 1) != '\n')
                { 
                        *l = '\0'; 
                       	initialize(++c);
                        last = ( l + 1); 
			atoken = 1;
                        awhite = 0;
			aredir = 0;
                }
		else if (*l == '\n')
		{
			*l = '\0';
			atoken = 1;
			awhite = 0;
			aredir = 0;
		}
                else if ( *l == '|' && *(l + 1) == '|' )
                {
                        cmds[c].boole = 1;
                        *l = '\0';
                        ++l;
                        *l = '\0';
                        initialize(++c);
                        last = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
                else if (*l == '|')
                {
                        cmds[c].piped = 1;
                        *l = '\0';
                        initialize(++c);
                        last = (l + 1); 
			atoken = 1;
                        awhite = 0;
			aredir = 0;
                }
                else if (*l == '&' && *(l + 1)  == '&')
                {
                        cmds[c].boole = 0;
                        *l = '\0';
                        ++l;
                        *l = '\0';
                        initialize(++c);
                        last = (l + 1); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
                else if (*l == '&')
                {
                        cmds[c].bg = 1;
                        *l = '\0';
                        initialize(++c);
                        last = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
                else if (*l == '>' && *(l + 1) == '>')
                {
                        *l = '\0';
                        ++l;
                        *l = '\0';
                        cmds[c].outflags = O_APPEND|O_RDWR|O_CREAT;
			while ( *( l + 1 ) == ' ') /* strip whitespace */
                                *l++ = '\0';
                        cmds[c].outfp = ( l + 1 );
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
                else if (*l == '>')
                {
                        *l = '\0';
                        cmds[c].outflags = O_TRUNC|O_RDWR|O_CREAT;
			while ( *( l + 1 ) == ' ') /* strip whitespace */
				*l++ = '\0';
                        cmds[c].outfp = ( l + 1 );
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
                else if (*l == '<')
                {
                        *l = '\0';
			while ( *( l + 1 ) == ' ') /* strip whitespace */
                                *l++ = '\0'; 
                        cmds[c].infp = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
		else if ( *l != ' ' && *l != '\t' )
		{
			if (aredir == 0 )
			{
				cmds[c].argv[cmds[c].argc] = last;
				cmds[c].argv[cmds[c].argc + 1] = NULL;/* speed up + hack */
			}
			awhite = 0;
			atoken = 0; 
		}
		else if ( *l == ' ' || *l == '\t' )
                { 
			if ( atoken == 0 && awhite == 0 && aredir == 0 && aquote == 0)
				cmds[c].argc++; 
			last = ( l + 1 );
                }
                ++l;
        }
	glb.count += c; 
	if ( glb.cmode )
		++glb.count; 
	if ( glb.testparse )
		verbosity();
	
        return 0; 
}
