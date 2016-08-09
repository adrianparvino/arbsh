
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

size_t date(char *, char *, size_t);
void datewrite(int, char *, size_t, int);

void datewrite(int desc, char *message, size_t len, int exitcode)
{
	write(desc, message, len);
	exit(exitcode);
}

size_t date(char *buf, char *format, size_t max)
{
        size_t n = 0;
        time_t t;
        struct tm *tm;
        if ((t = time(0)) == -1)
                return 0;
        if (!(tm = localtime(&t)))
                return 0;
        if ((n = strftime(buf, max, format, tm)) == 0)
                return 0;
	buf[n++] = '\n';
	buf[n++] = '\0';
        return n;
}

