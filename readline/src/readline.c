#include <readline/readline.h>

char *readline(char *prompt)
{ 
	size_t promptlen = strlen(prompt);
	size_t len = 0;

	char *l = malloc(len + 4096);
	
	hglb.r = 1; 
	
	while ( hglb.r )
	{
		determinewin(); 
		greadprint(l, len, prompt, promptlen); 
       		len = greadgetch(l);
	}

	return l;
}
