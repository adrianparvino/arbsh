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
} state;

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
	for (;lim--;++o)
	{ 
                if ( o->err == 0 && o->boole == 1 )	/* ||  */
                        continue; 
                if ( o->err != 0 && o->boole == 0 )	/* && */
                        continue;
		if ( o->infp != NULL )			/* < */
	                if((o->in = open(o->infp, O_RDONLY)) == -1);
	        if (o->outfp != NULL )			/* >, >> */
	       	        if((o->out = open(o->outfp, o->outflags, 0755)) == -1);
		if (o->piped == 1)			/* | */
		      	if((o = piped(o)));
		if ((o->pids = fork()) == 0) 
			o = child(o);
		o = foreground(o);
	}
}

int main(void)
{
	
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
	// o = parse(o, string);
	o = execute(o, 10);

	return 0;
}

