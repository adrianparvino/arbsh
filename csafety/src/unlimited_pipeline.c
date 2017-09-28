/*
Unix pipelines can be created between utilities without using a buffer of any
kind. Using the typical object it becomes simple to store the information
needed to seamlessly connect the stdin and stdout of a series of utilities.
Pipe() is not set up for the final command in the sequence. Presented below is
a small program that demonstrates the basics needed for writing a simple shell
that supports arbitrary numbers of pipes. The sequence used is equivalent to
"ls -l | wc -l | wc -l | wc -l | wc -l > outfile"
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
	} shell; 

	shell *piped(shell *o)
	{
		int fildes[2];
		if ((pipe(fildes)) == -1)
			return NULL;
		(o+1)->in = fildes[0];
		o->out = fildes[1];
		return o;
	}

	shell *child(shell *o)
	{
		dup2(o->in, STDIN_FILENO);
		dup2(o->out, STDOUT_FILENO);
		execvp(o->cmd[0], o->cmd);
		_exit(1);
		return o;
	}

	shell *foreground(shell *o)
	{
		waitpid(o->pids, &(o->err), 0);
		if (o->out != -1)
			close(o->out);
		if (o->in != -1)
			close(o->in);
		return o;
	}

	shell *execute(shell *o)
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
		shell p[10] = 
		{{{ "ls", "-l", NULL}, -1, -1, 0, 0, 1,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 ,NULL, NULL, 0, -1},
		{{ "wc", "-l", NULL}, -1, -1, 0, 0, 0 ,NULL, "outfile",
		O_APPEND|O_RDWR|O_CREAT, -1}};
	
		shell *o = p;
	
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
/*
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
*/
