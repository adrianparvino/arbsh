#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

typedef struct{ 
        char **cmd;
	int in;
	int out;
	pid_t pids;
	int err;
} object;

int main(void)
{ 
	int fildes[2];
	size_t lim = 10;

	object *o = malloc(sizeof(object) * 10);

	size_t i = 0;
	(o+i)->cmd = malloc(sizeof(char *) * 10);
	(o+i)->cmd[0] = "ls";	
	(o+i)->cmd[1] = "-l";	

	for(i=1;i<lim;++i)
	{
		(o+i)->cmd = malloc(sizeof(char *) * 10);
		(o+i)->cmd[0] = "wc";
		(o+i)->cmd[1] = "-l";
	}

	for(i=0;i<lim;++i)
	{
		
		if ( (o+i)->pids = fork() == 0)
		{ 
                        if ( pipe(fildes) == -1 )
                                return 0;
			(o+i)->in = fildes[0];
			(o+i)->out = fildes[1];
			dup2((o+i)->in, STDIN_FILENO);
                        
                        dup2((o+i)->out, STDOUT_FILENO);

                        //cmds[k + 1].in = fildes[0];
                        //cmds[k].out = fildes[1];
			
               
			execvp((o+i)->cmd[0], (o+i)->cmd);

			_exit(1);

			waitpid((o+i)->pids, &(o+i)->err, 0);

                       
		
                        close((o+i)->out);
                        
                        close((o+i)->in);
	
		} 
	}

	return 0; 
}

