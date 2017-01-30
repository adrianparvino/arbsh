/*
	Copyright 2017, CM Graff, "libgen.h"
	See LICENSE for copying details
*/

/* function prototypes */
char *gbasename(char *);
char *gdirname(char *);

/* functions */
char *gdirname(char *path)
{ 
	size_t i = strlen(path);
	for (; i && path[--i] == '/';)
		path[i] = 0;
	for (; i && path[i] != '/';)
		path[i--] = 0;
	for (; i && path[i] == '/';)
		path[i--] = 0;
	return path;
}

char *gbasename(char *path)
{
	size_t i = 0;
	int pathtab[4096] = { 0 };
	size_t npth = 0;

	for( i = 0; path[i] != '\0' && i < 4096; i++)
	{
		if ( path[i] == '/' )
			pathtab[npth++] = i;
	}

	for ( ; i > 1 && path[--i] == '/' ; )
	{
		path[i] = '\0';
		--npth;
	}

	if ( npth > 1)
		return path + pathtab[npth - 1] + 1; 
	else 
		return path;
}

