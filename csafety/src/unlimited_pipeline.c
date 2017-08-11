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

typedef struct{
	char *cmd[3];	/* command vector */
	int in;		/* stdin */
	int out;	/* stdout */
	pid_t pids;	/* for waitpid() */
	int err;	/* for waitpid() */
	int piped;	/* boolean value */
} object;

int main(void)
{ 
	int fildes[2];
	size_t lim = 10;
	size_t i = 0;

	object o[13] = {{{ "ls", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 0 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 0 }};

	object *p = o;
	
	for(i=0;i<lim;++i, ++p)
	{
		if (p->piped == 1)
		{
               		pipe(fildes);
			(p+1)->in = fildes[0];
			(p)->out = fildes[1];
		}
	
		if ((p->pids = fork()) == 0)
		{ 
			dup2(p->in, STDIN_FILENO); 
                        dup2(p->out, STDOUT_FILENO);
			execvp(p->cmd[0], (o+i)->cmd); 
			_exit(1); 
		} 
		
		waitpid(p->pids, &(p->err), 0);
		if (p->out != -1)
                	close(p->out);
		if (p->in != -1)
              		close(p->in);
	
	}

	return 0; 
}

