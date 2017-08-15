/*
Unix pipelines can be created between utilities without using a buffer of any
kind. Using the typical object it becomes simple to store the information 
needed to seamlessly connect the stdin and stdout of a series of utilities.
Pipe() is not set up for the final command in the sequence. Presented below is
a small program that demonstrates the basics needed for writing a simple shell 
that supports arbitrary numbers of pipes.
*/

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

typedef struct {
	size_t total;
	int _if;
	int _else;
	int _then;
	int _fi;
	size_t _while;
	size_t _for;
	object *o;
} state;

state *parse(state *s, object *o, char *str)
{
	s->total = 10;
}

object *piped(object *o)
{
	int fildes[2];
	pipe(fildes);
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

object *execute(object *o, size_t lim)
{ 
	if ( o->infp != NULL )			/* < */
	        if((o->in = open(o->infp, O_RDONLY)) == -1);
	if (o->outfp != NULL )			/* >, >> */
	        if((o->out = open(o->outfp, o->outflags, 0755)) == -1);
	if (o->piped == 1)			/* | */
	      	if((o = piped(o)));
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

	state q[1] = { 0 };
	state *s = q;
	s = parse(s, p, ""); 
	s->o = p;

	for (;i<s->total;s->o++,++i)
	{
        	if ((s->o-1)->err == 0 && (s->o-1)->boole == 1)	/* || */
	      	        continue; 
	        if ((s->o-1)->err != 0 && (s->o-1)->boole == 0)	/* && */
	                continue;
		s->o = execute(s->o, 10);
	}

	return 0;
}


int parserold(char *l)
{ 
	/* grammar */
	int atoken = 0;
	int awhite = 1;
	int aredir = 0; 
	/* total commands */
	size_t c = 0; 
	/* remain at the start of a command sequence */
	char *last; 
	/* intialialize a data structure member and the pointer to input */
	//initialize(c);
        last = l;

	/* discover tokens and commands */
        while ( *l )
        { 
		if (*l == ';')
                {
                        *l = '\0';
                        //initialize(++c);
                        last = ( l + 1 ); 
			atoken = 1;
			awhite = 0;
			aredir = 0;
                }
		else if (*l == '\n' && *(l + 1) != '\n')
                { 
                        *l = '\0'; 
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
                        //cmds[c].boole = 1;
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
                        //cmds[c].piped = 1;
                        *l = '\0';
                        //initialize(++c);
                        last = (l + 1); 
			atoken = 1;
                        awhite = 0;
			aredir = 0;
                }
                else if (*l == '&' && *(l + 1)  == '&')
                {
                        //cmds[c].boole = 0;
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
                        //cmds[c].bg = 1;
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
                        //cmds[c].outflags = O_APPEND|O_RDWR|O_CREAT;
			while ( *( l + 1 ) == ' ') /* strip whitespace */
                                *l++ = '\0';
                        //cmds[c].outfp = ( l + 1 );
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
                else if (*l == '>')
                {
                        *l = '\0';
                        //cmds[c].outflags = O_TRUNC|O_RDWR|O_CREAT;
			while ( *( l + 1 ) == ' ') /* strip whitespace */
				*l++ = '\0';
                        //cmds[c].outfp = ( l + 1 );
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
			atoken = 1;
			awhite = 0;
			aredir = 1;
                }
		else if ( *l != ' ' && *l != '\t' )
		{
			if (aredir == 0 )
			{
				//cmds[c].argv[cmds[c].argc] = last;
				//cmds[c].argv[cmds[c].argc + 1] = NULL;/* speed up + hack */
			}
			awhite = 0;
			atoken = 0; 
		}
		else if ( *l == ' ' || *l == '\t' )
                { 
			if ( atoken == 0 && awhite == 0 && aredir == 0)
				;//cmds[c].argc++; 
		
			awhite = 1;
                       	*l = '\0';
			last = ( l + 1 );
                }
                ++l;
        } 
        return 0; 
}
