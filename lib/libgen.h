/*
	Copyright 2017, CM Graff, "libgen.h"
	See LICENSE for copying details
*/

/* function prototypes */
char *gbasename(char *);
char *gdirname(char *);
char *ggnu_basename(char *path);

/* functions */
char *gbasename(char *str) /* not yet implemented */
{
	return str;
}

char *gdirname(char *str)  /* not yet implemented */
{
	return str;
}

char *ggnu_basename(char *path) /* non-POSIX GNU version of basename */
{
	char *base = strrchr(path, '/');
	return base ? base+1 : path;
}