#include <stdio.h> 
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
        char *userline = malloc(BUFSIZ * sizeof(char));
	size_t len = 0;
	
        while ( 1 )
        {
		userline[0] = '\0'; 
                len = ircline(userline, "[ircline]>> ", 12);
		printf ("Finished line was: \n%s\n", userline);
		add_history(userline);
        }
	//free(hist);
        return 0;
}


