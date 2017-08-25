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
	char *cmd[1024];	/* command vector */
	size_t argc;
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
object *parse(object *o, char *l);

struct commands
{
	/* commands */
	char *cmd[1024]; 
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

init(object *o)
{ 
	o->cmd[0] = NULL;
        o->argc = 0;
        o->outflags = O_APPEND|O_RDWR|O_CREAT;
        o->outfp = NULL;
        o->infp = NULL;
        o->in = -1;
        o->out = -1;
        //o->bg = 0;
        o->piped = 0;
        o->err = 0;
        o->boole = -1;
}

int main(void)
{
	size_t i = 0;
	

	object *p = malloc(sizeof(object) * 10);
	
	object *o = p;
	char str[12] = { 'l', 's', ' ', '|', ' ', 'w', 'c', 0};
	//char str[12] = { 'l', 's', ' ', '-', 'l', 0};
	//char str[12] = { 'l', 's', ';', 'l', 's', 0 };
	
	for (o=p;i<10;o++,++i)
		o = init(o);
	
	parse(o=p, str);

	for (o =p,i=0;i<glb.count;o++,++i)
	{
       	 	//if (i && (o-1)->err == 0 && (o-1)->boole == 1)	/* || */
	      	//        continue; 
	        //if (i && (o-1)->err != 0 && (o-1)->boole == 0)	/* && */
	        //        continue; 
		o = execute(o);
	}
	
	return 0;
} 

/* functions */
/*
void verbosity(void)
{
        size_t i = 0;
        size_t j = 0;

	fprintf(stderr, "Total command vectors: %zu \n",glb.count);
        
        for (i = 0; i < glb.count ;i++)
        {
		fprintf(stderr, "\n");
		
                for ( j = 0; j <= cmds[i].argc ; ++j) 
                        fprintf(stderr, "%s\t\tcmd           %zu\n", cmds[i].cmd[j], j); 
                if ( cmds[i].infp != NULL )
                        fprintf(stderr, "%s\t\tin  <   vector %zu\n", cmds[i].infp, i);
                if ( cmds[i].outfp != NULL ) 
                        fprintf(stderr, "%s\t\tout >   vector %zu\n", cmds[i].outfp, i); 
        }
	if ( glb.inascript)
		exit(1);
}
*/
object *parse(object *o, char *l)
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
	//initialize(c);
	++c;
        last = l;

	/* discover tokens and commands */
        while ( *l )
        { 
		if (*l == ';')
                {
                        *l = '\0';
			++o;
                        //initialize(++c);
                        last = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
		else if (*l == '\n' && *(l + 1) != '\n')
                { 
                        *l = '\0'; 
			++o;
                       	//initialize(++c);
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
                        
			o->boole = 1;
			++o;
                        *l = '\0';
                        ++l;
                        *l = '\0';
                        //initialize(++c);
                        last = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
                else if (*l == '|')
                {
                        
			o->piped = 1;
			++o;
			++c;
                        *l = '\0';
                        //initialize(++c);
                        last = (l + 1); 
			atoken = 1;
                        awhite = 0;
			aredir = 0;
                }
                else if (*l == '&' && *(l + 1)  == '&')
                {
                        
			o->boole = 0;
                        *l = '\0';
                        ++l;
                        *l = '\0';
                        //initialize(++c);
                        last = (l + 1); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
                else if (*l == '&')
                { 
			//o->bg = 1;
                        *l = '\0';
                        //initialize(++c);
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
			o->outflags = O_APPEND|O_RDWR|O_CREAT;
			while ( *( l + 1 ) == ' ') /* strip whitespace */
                                *l++ = '\0'; 
			o->outfp = ( l + 1 );
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
                else if (*l == '>')
                {
                        *l = '\0'; 
			o->outflags = O_TRUNC|O_RDWR|O_CREAT;
			while ( *( l + 1 ) == ' ') /* strip whitespace */
				*l++ = '\0'; 
			o->outfp = ( l + 1 );
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
                else if (*l == '<')
                {
                        *l = '\0';
			while ( *( l + 1 ) == ' ') /* strip whitespace */
                                *l++ = '\0'; 
                        //cmds[c].infp = ( l + 1 ); 
			//o->infp = ( l + 1 );
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
		else if ( *l != ' ' && *l != '\t' )
		{
			if (aredir == 0 )
			{ 
				o->cmd[o->argc] = last;
				o->cmd[o->argc + 1] = NULL;
			}
			awhite = 0;
			atoken = 0; 
		}
		else if ( *l == ' ' || *l == '\t' )
                { 
			if ( atoken == 0 && awhite == 0 && aredir == 0 ) 
				o->argc++;
			*l = 0;
			awhite = 1;
			last = ( l + 1 );
                }
                ++l;
        }
	glb.count += c; 
	if ( glb.cmode )
		++glb.count; 
	//if ( glb.testparse )
		//verbosity();
	
        return o; 
}
