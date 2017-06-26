#include <readline/readline.h>
char * find_pattern(char *path, size_t tot, char *pat, size_t patlen);
char * find_pattern(char *path, size_t tot, char *pat, size_t patlen)
{
        DIR *dir;
        struct dirent *d;
        size_t dlen = 0;
	size_t last;
	size_t matches = 0;
	char *match = NULL;
	char spath[READLINE_LIMIT];
	spath[0] = 0;
	
	size_t i = 0;
	int lever = 0;

        if ( ( dir = opendir(path) ) )
        {
                d = readdir(dir);
                while (d)
                {
                        dlen = strlen(d->d_name); 
                        tot = sprintf(spath, "%s/%s", path, d->d_name); 
                        if ( strcmp( ".", d->d_name) &&
                           ( strcmp( "..", d->d_name)) )
                        {
				lever = 0;
				if (dlen < patlen)
					lever = 1;
				for (i=0; i<patlen;++i)
				{
					if (pat[i] != d->d_name[i]) 
						lever = 1;
				}
				if ( lever == 0)
				{ 
					if ( match == NULL ) 
					{
						match = malloc(READLINE_LIMIT);
						strcpy(match, spath);
					}else
					printf("%s\n", spath);
					++matches;
				}
                        }
                        d = readdir(dir);
                }
		if ( matches == 1 ) 
		{
			return match; 
		} 
        } 
        closedir(dir);
        return NULL;
}

size_t greadgetch(char *l, size_t linelen, char *prompt, size_t plen)
{
        static size_t len = 0;
	static size_t ret = 0;
	size_t z = 0;
        int c;
	char *line = NULL;
       
	c = readchar(); 
        
        switch (c) { 
	case K_ESCAPE:
		c = readchar();
		switch (c) {
		case '[':
                        c = readchar();
			switch (c) { 
			case 'A': /* arrow up */
				if ( hglb.c > 0 )
				{
					--hglb.c; 
					memcpy(l, hist[hglb.c].line, hist[hglb.c].len);
					len = hist[hglb.c].len;
					hglb.laro = 0;
				}
				break;
			case 'B': /* arrow down */
				if ( hglb.c < hglb.t)
				{
					++hglb.c;
					if ( hglb.c < hglb.t)
					{
						memcpy(l, hist[hglb.c].line, hist[hglb.c].len);
						len = hist[hglb.c].len;
					}else
						len = 0;
					hglb.laro = 0;
				}
				break;
			case 'C': /* right arrow */ 
				if ( hglb.laro > 0 )
					--hglb.laro;
                                break;
			case 'D': /* left arrow */ 
				if ( hglb.laro < len )
					++hglb.laro; 
				break; 
			case 'H': /* Home */
				hglb.laro = len;
                                break;
			case '5': /* page up ( not used ) */ 
				c = readchar(); 
				break;
			case '6': /* page down ( not used ) */ 
				c = readchar();
				break;
			}
		}
		return len;
	case '\t':
		l[len] = 0;
		char pat[4096] = { 0 };
		size_t z = len;
		size_t y = 0;
		size_t point = 0;
	
		for ( ;z > 0;--z ,++y)
		{
			if (l[z] == '/' && point == 0)
				point = y;
			if (l[z] == ' ' )
				break; 
		}

		memcpy(pat, l + (len -y) + 1, y + 1);
		pat[(y -point)] = 0;
		//printf("\n%s\n", l);
		//printf("\n%s\n", pat);
		//printf("\n%s\n", l + (len -point) + 1); 
		
		if ((line = find_pattern(pat, strlen(pat), l +  (len -point) + 1, strlen(l +  (len -point) + 1))))
		{ 
			sprintf(l + (len -y) + 1, "%s", line);
			len = strlen(l); 
		
		//write(1, "\r", 1);
		
		//write(1, T_CLRCUR2END, T_CLRCUR2END_SZ);
		//write(1, l, len);
		//write(1, prompt, plen);
		}	
		
		//len = 0;
		//l[len] = 0;
	
		
		l[len] = '\0';
		return len;
		break;
        case '\n':
		write(1, "\n", 1);
		l[len] = '\0';
		ret = len;
		len = 0;
		hglb.r = 0;
		hglb.laro = 0;
                return ret;
	case K_BACKSPACE:
		if ( len == 0 )
			return len;
		if ( hglb.laro ) 
		{
			z = (len - hglb.laro);
                        memmove(l + z - 1, l + z, hglb.laro);
		}
		l[--len] = '\0';
		return len; 
        default:
		/* this needs to check that memmove() can't 
		   go out of bounds
		*/
		if ( hglb.laro )
		{
			z = (len - hglb.laro);
			memmove(l + z + 1, l + z, hglb.laro);
			l[z] = c; 
		}
		else { 
			l[len] = c;
		} 
		if ( len < READLINE_LIMIT -1)
			l[++len] = '\0'; 
	
                break;
        }

	l[len] = '\0';
	return len;
}
