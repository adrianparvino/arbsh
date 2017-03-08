#include <glibgen.h>

char *gdirname(char *path)
{ 
	size_t i = gstrlen(path);
	for (; i && path[--i] == '/';)
		path[i] = 0;
	for (; i && path[i] != '/';)
		path[i--] = 0;
	for (; i && path[i] == '/';)
		path[i--] = 0;
	return path;
}
