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

object *piped(object *p)
{
	int fildes[2];
        pipe(fildes);
        (p+1)->in = fildes[0];
        p->out = fildes[1];
	return p;
}

object *child(object *p)
{
       dup2(p->in, STDIN_FILENO);
       dup2(p->out, STDOUT_FILENO);
       execvp(p->cmd[0], p->cmd);
       _exit(1);
	return p;
}

object *execute(object *p, size_t lim)
{
        if (p->piped == 1)
              	p = piped(p);
        if ((p->pids = fork()) == 0) 
		p = child(p);
        waitpid(p->pids, &(p->err), 0);
        if (p->out != -1)
                close(p->out);
        if (p->in != -1)
                close(p->in);
	if (lim)
		return	p = execute(p+1, lim-1); 
}

int main(void)
{ 
	
	object o[10] = {{{ "ls", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 1 },
	{{ "wc", "-l", NULL}, -1, -1, 0, 0, 0 }};

	object *p = o;

	p = execute(p, 10);

	return 0;
}

