#include <readline/readline.h>
int find_pattern(char *path, size_t tot, size_t last);

int find_pattern_wrap(char *path, size_t tot, size_t last)
{
	char *temp=malloc(4095);;
	strcpy(temp, path);
	temp = basename(temp);
	find_pattern(temp, tot, last);
}

int find_pattern(char *path, size_t tot, size_t last)
{
        DIR *dir;
        struct dirent *d;
        char *spath = NULL;
        size_t dlen = 0;

        if ( ( dir = opendir(path) ) )
        {
                d = readdir(dir);
                while (d)
                {
                        dlen = strlen(d->d_name);

                        last = (tot + dlen + 2); /* +2 = '/' + '\0' */
                        spath = realloc(spath, last);
                        if (!(spath))
                                return -1;
                        tot = sprintf(spath, "%s/%s", path, d->d_name);

                        if ( strcmp( ".", d->d_name) &&
                           ( strcmp( "..", d->d_name)) )
                        {
                                printf("%s\n", spath);
                        }
                        d = readdir(dir);
                }

        }
        if ( spath)
                free(spath);
        closedir(dir);
        return 0;
}



size_t greadgetch(char *l)
{
        static size_t len = 0;
	static size_t ret = 0;
	size_t z = 0;
        int c;
       
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
		find_pattern(l, len, 0);
		
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
		/* this is wrong and needs to check that memmove() can't 
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
