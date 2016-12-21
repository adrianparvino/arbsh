int find_pattern(char *path, size_t tot, size_t last)
{ 
	DIR *dir;
	struct dirent *d;
	char *spath = malloc (1);
	size_t dlen = 0; 

	if (!(spath))
		return -1;
	
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

			if ( d->d_type == DT_DIR &&
			   ( strcmp( ".", d->d_name)) &&
			   ( strcmp( "..", d->d_name))) 
				find_pattern(spath, tot, last); 
			d = readdir(dir); 
		}
		
	}
	free(spath);
	closedir(dir);
	return 0;
}

