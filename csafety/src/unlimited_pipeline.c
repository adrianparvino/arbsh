/*
Unix pipelines can be created between utilities without using a buffer of any
kind. Using the typical object it becomes simple to store the information 
needed to seamlessly connect the stdin and stdout of a series of utilities.
Pipe() is not set up for the final command in the sequence. Presented below is
small program that demonstrates the basics needed for writing simple shell that
supports arbitrary numbers of pipes.
*/

#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
	char *cmd[10];	/* command vector */
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

	object *o = malloc(sizeof(object) * lim);
	
	for(i=0;i<lim;++i) /* set all command vectors to "wc -l" */
	{
		(o+i)->cmd[0] = "wc"; 
		(o+i)->cmd[1] = "-l";
		(o+i)->cmd[2] = NULL; /* exec* depends in a terminating NULL */
		(o+i)->in = -1;
		(o+i)->out = -1;
		(o+i)->piped = 1;
	}
	(o)->cmd[0] = "ls"; /* reset the first command vector to be "ls -la" */
	(o+i -1)->piped = 0; /* the final command is not piped! */
	
	for(i=0;i<lim;++i)
	{ 
		if ((o+i)->piped == 1)
		{
               		pipe(fildes);
			(o+(i+1))->in = fildes[0];
			(o+i)->out = fildes[1];
		}
	
		if ( ((o+i)->pids = fork()) == 0)
		{ 
			dup2((o+i)->in, STDIN_FILENO); 
                        dup2((o+i)->out, STDOUT_FILENO); 
			
			execvp((o+i)->cmd[0], (o+i)->cmd); 
			_exit(1); 
		} 
		
		waitpid((o+i)->pids, &((o+i)->err), 0);
		if ((o+i)->out != -1)
                	close((o+i)->out);
		if ((o+i)->in != -1)
              		close((o+i)->in);
	}

	return 0; 
}

