#include <gstdio.h> 
int putchar(int x)
{
	return gputc(x, gstdout);
}
