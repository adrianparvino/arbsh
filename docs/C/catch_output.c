#include <unistd.h>


int main(int argc, char *argv[])
{
	int pipefd[2] = { 0 };
	char buffer[1024] = { 0 };
	ssize_t len = 0;
	size_t total = 0; 

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
			while (len = read(pipefd[0], buffer, sizeof(buffer)))
			{
				if ( len == 0 )
					break;
				total +=len;
			}
			write(1, buffer, total);
		}
	}
	return 0;
}

