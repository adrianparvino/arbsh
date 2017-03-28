#include <gstdio.h>

GFILE *gpopen(const char *command, const char *type)
{
	GFILE *ret = gstdout;
	int pipefd[2] = { 0 };
        ssize_t len = 0;
        size_t total = 0;
        char *buffer;
	size_t bufsize = 4096; 
	

        if (!(buffer = malloc(bufsize)))
                return 0;
        pipe(pipefd);

	ret->pid = fork();
	ret->fd = pipefd[0];
	close(pipefd[1]);

        if (ret->pid == 0)
        {
		char *argv[] = { "/bin/sh", "-c", NULL, NULL};
		argv[2] = command;
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                close(pipefd[1]);
                dup2(pipefd[1], 2);
                execvp(argv[0], argv);
                _exit(1);
        }
        else
        {
                //close(pipefd[1]);
		
		/*
                while ((len = read(pipefd[0], buffer + total, PIPE_BUF)))
                {
                        total +=len;
                        if (!(buffer = realloc(buffer, total + PIPE_BUF + 1)))
                                return 0;
                } 
                write(1, buffer, total);
		*/
        }
	
	return ret;
}

int gpclose(GFILE *fp)
{
	int ret = 0;
	
	/* needs to call wait4 */
	fp->pid = 0;
	gfclose(fp);
	return ret;
}
