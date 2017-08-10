#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

typedef struct{ 
        char **cmd;
	int in;
	int out;
} object;

int main(void)
{ 
	int filedes[2];
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
		if ( fork() == 0)
		{
			execvp((o+i)->cmd[0], (o+i)->cmd);
			_exit(1);
		} 
	}

	return 0; 
}

