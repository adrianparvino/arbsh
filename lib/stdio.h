/*
	Copyright 2017. CM Graff "stdio.h"
	See LICENSE for copying details
*/

/* defines */
/* ------- */
#define GBUFSIZEE 4096
#define IRCBUFSIZ GBUFSIZEE
//#define HASLIBM

/* self hosting dependencies */
/* ------------------------- */
#include <stddef.h>
#include <stdarg.h>

/* local libraries */
/* --------------- */
#include "itoa.h"
#ifdef HASLIBM
#include "dtoa.h"
#endif
#include "file.h"

/* function declarations */
/* --------------------- */
int ggetchar(void);
int gputchar(char);
size_t ggetline(char [], int);
int gprintf_inter(int, char *, size_t, int, char *, va_list);
int gprintf(char *, ...);
int gsprintf(char *, char *, ...);
int gsnprintf(char *, size_t, char *, ...);
int gdprintf(int, char *, ...);
int gvprintf(char *, va_list);
int gvsprintf(char *, char *, va_list);
int gvsnprintf(char *, size_t, char *, va_list);
int gvdprintf(int, char *, va_list);

/* functions */
/* --------- */

/* single char io  */
int ggetchar(void)
{ 
	static char buf[GBUFSIZEE];
	static char *bufp = buf;
	static size_t i = 0;

        if (i >= (GBUFSIZEE - 1))
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

/* printf family (variadic and formatted) */
int gprintf_inter(int fd, char *str, size_t lim, int flag, char *fmt, va_list ap)
{ 
	char *p = NULL;
	char *out;
	int i = 0;
	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0; 
	int dval = 0; 
	long lval = 0;
#ifdef HASLIBM
	double fval = 0;
	char ftemp[1025]= { 0 };
#endif

	if (flag == 0) /* printf */
		out = malloc(1025); 
	if (flag == 1 || flag == 2) /* sprintf, snprintf */
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
			case 'f': 
#ifdef HASLIBM
				fval = va_arg(ap, double); 
				gdtoa(ftemp, fval - (long)fval); 
				i += gsprintf(out + i, "%ld", (long)fval);
				i += gsnprintf(out + i, 7, "%s", ftemp + 1);
#endif
				break;
			case 'l':
				switch (*++p)
				{ 
					case 'd':
						lval = va_arg(ap, long);
						i += intostrbase(out + i, lval, 10);
						break;
					case 'f': 
#ifdef HASLIBM
						fval = va_arg(ap, double);
						gdtoa(ftemp, fval - (long)fval);
						i += gsprintf(out + i, "%ld", (long)fval);
						i += gsnprintf(out + i, 7, "%s", ftemp + 1);
#endif
						break;
					default:
						break;
				}
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

	
	if ( flag == 2) 
		i = lim;

	out[i + 1] = '\0';


	if ( flag == 0 )
		i = write(fd, out, i); /* if writing to an fd, then redefine the ret */

	return i;
}

int gprintf(char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsprintf(char *str, char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsnprintf(char *str, size_t lim, char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gdprintf(int fd, char *fmt, ...)
{
	int ret  = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gvprintf(char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsprintf(char *str, char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsnprintf(char *str, size_t lim, char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvdprintf(int fd, char *fmt, va_list argptr)
{
	int ret  = 0;
	ret = gprintf_inter(fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

