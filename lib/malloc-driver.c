#include <stdio.h>
#include <dirent.h>
#include <fnmatch.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
//#include "string.h"
#include "stdlib.h"
#include "stdio.h"

int find_pattern(char *, size_t, size_t);

int main(int argc, char *argv[])
{
	if (argc > 1)
		find_pattern(argv[1], gstrlen(argv[1]), 0);
	else
		find_pattern(".", 1, 0);
	return 0;
}

int find_pattern(char *path, size_t tot, size_t last)
{ 
	DIR *dir;
	struct dirent *d;
	char *spath = gmalloc (1);
	size_t dlen = 0; 

	if (!(spath))
		return -1;
	
	if ( ( dir = opendir(path) ) ) 
	{
		d = readdir(dir); 
		while (d) 
		{ 
			dlen = gstrlen(d->d_name); 
			
			last = (tot + dlen + 2); /* +2 = '/' + '\0' */
			spath = grealloc(spath, last);
			if (!(spath))
				return -1;
			tot = gsprintf(spath, "%s/%s", path, d->d_name);
	
			if ( gstrcmp( ".", d->d_name) && 
			   ( gstrcmp( "..", d->d_name)) )
			{
				gprintf("%s\n", spath);
			}

			if ( d->d_type == DT_DIR &&
			   ( gstrcmp( ".", d->d_name)) &&
			   ( gstrcmp( "..", d->d_name))) 
				find_pattern(spath, tot, last); 
			d = readdir(dir); 
		}
		
	}
	gfree(spath);
	closedir(dir);
	return 0;
}

