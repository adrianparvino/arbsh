#include <gstdio.h>

GFILE *gpopen(const char *command, const char *type)
{
	GFILE *ret = gfopen(NULL, type);
	int pipefd[2] = { 0 };

	if (ret == NULL)
		return ret;

        pipe(pipefd);
	ret->pid = fork();
	ret->fd = pipefd[0];
        if (ret->pid == 0)
        {
		char *argv[] = { "/bin/sh", "-c", NULL, NULL};
		argv[2] = (char *)command;
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                close(pipefd[1]);
                dup2(pipefd[1], 2);
                execvp(argv[0], argv);
                _exit(1);
        }
        else
        {
                close(pipefd[1]); 
        }
	
	return ret;
}
