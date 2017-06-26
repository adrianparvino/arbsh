#include <readline/readline.h>
char * find_pattern(char *path, size_t tot, char *pat, size_t patlen);
char *find_pattern_wrap(char *path, size_t tot, size_t last);



char *tokenize(char *l)
{
	size_t i = 0;
	size_t len = 0;
	int inas = 1;
	char *ret = malloc(READLINE_LIMIT);
	size_t j = 0;
	size_t k = 0;
	char *p = l;
	//char tokens[100][READLINE_LIMIT] = { 0 }; // only need the final token
	while (1)
	{
		if (*l == ' ' || *l == 0)
		{
			if ( inas == 0 )
			{
				k = j;
				++i;
			}
			inas = 1;
			len = 0;
			if (*l == 0)
				break;
		}
		else
			inas = 0;
	
		if (*l != ' ')
		{
			//tokens[i][len] = *l;
			//tokens[i][len + 1] = 0;
			ret[len] = *l;
			ret[len + 1] = 0;
			++len;
		}
		++l;
		++j;
	} 
	p[k] = 0;
	printf("\nreserve %s\n", p);
	//for (j=0;j<i;++j) 
	//	printf("\n%s\n", tokens[j]);
	return find_pattern_wrap(ret, len, 0);
	
}

char *find_pattern_wrap(char *path, size_t tot, size_t last)
{
	if (!(*path))
		return;

	char *pathnam = malloc(4095);; 
	char *pattern = malloc(4095);; 
	char *ret = NULL;

	strcpy(pathnam, path);

	tot = strlen(path) -1;

	if (path[tot] == '/')
	{
		pattern = "";
	}else
	{
		strcpy(pattern, path);
		pathnam = dirname(pathnam);
		pattern = basename(pattern);
	} 

	printf("\n");
	printf("dirname :%s\n", pathnam);
	printf("basename :%s\n", pattern);
	ret = find_pattern(pathnam, strlen(pathnam), pattern, strlen(pattern));

	return ret;
}

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
			//memcpy(spath, path, tot);
			//memcpy(spath + tot, "/", 1);
			//memcpy(spath + tot + 1, d->d_name, dlen);
			//spath[tot + 1 + dlen] = 0;

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
						//memcpy(match, spath, tot + 1 + dlen + 1);
						//memcpy(match, spath, tot + 1);
					}
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



size_t greadgetch(char *l)
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
	
		for ( ;z > 0;--z ,++y)
		{
			if (l[z] == ' ' )
				break; 
		}
		memcpy(pat, l + (len -y) + 1, y + 1);
	
		
		//printf("\n%s\n", l);
		//printf("\n%s\n", pat);
	
		if ((line =find_pattern_wrap(pat, y, 0)))
		{
			len += sprintf(l + (len -y) + 1, "%s", line);
		
		}
		


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
