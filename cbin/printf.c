#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

void binprintf(void);

int main(int argc, char *argv[])
{
	//int vsprintf(char *str, const char *format, va_list ap);
	char s[4096];
	//vsprintf(s, "%s", argv[1]);
	return 0; 
}

void binprintf(void)
{
	;
}
