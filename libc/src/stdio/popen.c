#include <gstdio.h>

GFILE *gpopen(const char *command, const char *type)
{
	GFILE *ret;
	int pipefd[2] = { 0 };
	char *argv[] = { "/bin/sh", "-c", NULL, NULL};

	if ((ret = gfopen(NULL, type)) == NULL)
		return NULL;
	if (command == NULL)
		return NULL;
        if ((pipe(pipefd)) == -1)
		goto error;
	if ((ret->pid = fork()) == -1)
		goto error;

	ret->fd = pipefd[0];

        if (ret->pid == 0)
        {
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

	error:
		gpclose(NULL);
		return NULL;
}		
