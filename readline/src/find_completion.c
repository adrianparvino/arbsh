#include <readline/readline.h>

char * find_pattern(char *path, size_t tot, char *pat, size_t patlen)
{
        DIR *dir;
        struct dirent *d;
        size_t dlen = 0;
	size_t last;
	size_t matches = 0;
	char *match = NULL;
	char **names;
	size_t n = 0;
	size_t i = 0;
	int lever = 0;
	size_t z = 0;
	size_t pp = strlen(path);
	if (!(names = malloc (sizeof(*names))))
		return NULL;
	if (!(names[n] = malloc(256)))
		return NULL;
	names[n][0] = 0; 

        if ( ( dir = opendir(path) ) )
        {
                d = readdir(dir);
                while (d)
                {
                        dlen = strlen(d->d_name); 
                        if ( strcmp( ".", d->d_name) &&
                           ( strcmp( "..", d->d_name)) )
                        {
				if ((pp && path[pp-1] == '/'))
					tot = sprintf(names[n], "%s%s", path, d->d_name); 
				else 
					tot = sprintf(names[n], "%s/%s", path, d->d_name);

				lever = 0;
				if (dlen < patlen)
					lever = 1;
				for (i=0; i<patlen;++i)
					if (pat[i] != d->d_name[i])
						lever = 1;
				if ( lever == 0)
				{ 
					if (match == NULL) 
						match = names[n];
					++matches;
					if (!(names = realloc(names, sizeof(*names) * (n++ + 10))))
						return NULL;
					if (!(names[n] = malloc(256)))
						return NULL;
					names[n][0] = 0; 
				} 
                        }
                        d = readdir(dir);
                } 
		if ( matches == 1 ) 
		{
			for(z= 0; z < n;++z) 
				if (names[z] != match)
					free(names[z]);
			return match; 
		} else{
			printf("\n");
			for(z= 0; z < n;++z )
			{
				printf("%s\n", names[z]);
				free(names[z]);
			}
		}
        }
        closedir(dir);
        return NULL;
}

