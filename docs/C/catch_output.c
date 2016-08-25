#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	int pipefd[2] = { 0 };
	ssize_t len = 0;
	size_t total = 0; 
	char *buffer;

	if (!(buffer = malloc(PIPE_BUF)))
		return 0;
	pipe(pipefd); 

	/* Usage: ./catch_output ls -la */
	if (argc > 1)
	{
		if (fork() == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			dup2(pipefd[1], 2);

			execvp(argv[1], argv + 1);
			_exit(1);
		}
		else
		{
			close(pipefd[1]);
			while ((len = read(pipefd[0], buffer + total, PIPE_BUF)))
			{
				total +=len;
				if (!(buffer = realloc(buffer, total + PIPE_BUF + 1)))
					return 0;
			}
	
			write(1, buffer, total);
		}
	}
	return 0;
}

