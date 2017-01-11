#define GBUFSIZ 4096
#define IRCBUFSIZ GBUFSIZ

#include <stddef.h>
#include <stdarg.h>

#include "itoa.h"

/* single char io  */
int ggetchar(void)
{ 
	static char buf[GBUFSIZ];
	static char *bufp = buf;
	static size_t i = 0;

        if (i >= (GBUFSIZ - 1))
		return -1;
	
	if (i == 0) 
	{
		i = read(0, buf, 1);
		bufp = buf;
	}
	
        if ( i-- )
		return  *bufp++;

	return -1;
} 

int gputchar(char c)
{ 
	char buf[1];
	buf[0] = c;
	return write(1, buf, 1);
}

/* line retrieval */
size_t ggetline(char s[], int lim)
{
        int c;
        size_t i = 0;
        while (--lim > 0 && (c=ggetchar()) != -1 && c != '\n')
                s[i++] = c;
        if (c == '\n')
                s[i++] = c;
        s[i] = '\0';
        return i;
}

/* printf family (variadic formatted) */
int gprintf_inter(char *str, int flag, char *fmt, va_list ap)
{ 
	char *p = NULL;
	char *out;
	size_t i = 0; /* this should be an int according to the IEEE */
	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0; 
	int dval = 0; 

	if (flag == 0) /* printf */
		out = malloc(1025); 
	if (flag == 1) /* sprintf */
		out = str; 

	for (p = fmt; *p; p++) 
	{
		if (*p != '%')
		{
			out[i++] = *p;
			continue;
		}
		switch (*++p)
		{
			case 'c':
				cval = va_arg(ap, int);
				out[i++] = cval;
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++) 
					out[i++] = *sval; 
				break;
			case 'd': 
				dval = va_arg(ap, int);
				i += intostrbase(out + i, dval, 10);
				break;
			case 'z':
				switch (*++p)
				{ 
					case 'u':
						zuval = va_arg(ap, size_t);
						i += uintostrbase(out + i, zuval, 10);
					default:
						break;
				}
				break;
			default:
				out[i++] = *p;
				break;
		}
	}
	out[i + 1] = '\0';
	if ( flag == 0 )
		write(1, out, i); 

	return i;
}

int gprintf(char *fmt, ...)
{
	size_t ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsprintf(char *str, char *fmt, ...)
{
	size_t ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(str, 1, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gdprintf(char *str, char *fmt, ...)
{
	size_t ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(str, 1, fmt, argptr);
	va_end(argptr);
	return ret;
} 

