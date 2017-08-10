#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{ 
        char **cmd;
	//char *cmd[10];
	int in;
	int out;
	pid_t pids;
	int err;
	int piped;
} object;

int main(void)
{ 
	int fildes[2];
	size_t lim = 10;
	size_t i = 0;

	object *o = malloc(sizeof(object) * lim);
	//object o[12];
	
	for(i=0;i<lim;++i)
	{
		(o+i)->cmd = malloc(sizeof((o+i)->cmd) * 10);
		(o+i)->cmd[0] = malloc(sizeof(char) * 10);
		(o+i)->cmd[1] = malloc(sizeof(char) * 10); 
		(o+i)->cmd[0] = "wc";
		(o+i)->cmd[1] = "-l";
		(o+i)->in = -1;
		(o+i)->out = -1;
		(o+i)->piped = 1;
	}
	(o)->cmd[0] = "ls"; 
	(o+i -1)->piped = 0;
	

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
		
		//waitpid((o+i)->pids, &(o+i)->err, 0);
                close((o+i)->out);
                close((o+i)->in);
	
	}

	return 0; 
}

