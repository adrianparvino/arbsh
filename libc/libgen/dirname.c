#include "libgen.h" 

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
