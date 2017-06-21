#include <readline/readline.h>

extern void add_history(const char *l)
{
	size_t len = strlen(l);
	if ( len > 1)
        { 
		if (!(hist = realloc(hist, sizeof(struct hist) * ( hglb.t + 1))))
                	return; // This _must_ be changed to a fatal error 
        	//strcpy(hist[hglb.t].line, l);
		memcpy(hist[hglb.t].line, l, len + 1);
		hist[hglb.t].len = len;
        	++hglb.t;
        }
	hglb.c = hglb.t;
}

