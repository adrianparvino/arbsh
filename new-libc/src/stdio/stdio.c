#include "fcntl.h" 
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define EOF	    -1

#ifndef SEEK_CUR
#define SEEK_CUR	0
#define SEEK_END	1
#define SEEK_SET	2
#endif

#define BUFSIZ		1024
#define FOPEN_MAX	20

#define _PRINTF_NAN -(0./0.)

typedef struct {
	int fd;
	char flags;
	char *buf;
	char *rp;
	char *lp;
	int len;
} GFILE;

GFILE _IO_stream[FOPEN_MAX];

enum _flags {
	_READ  = 001,
	_WRITE = 002,
	_UNBUF = 004,
	_EOF   = 010,
	_ERR   = 020,
};

char *gfgets(char *s, int n, GFILE *iop);
int gfputs(char *s, GFILE *iop);
int _fillbuf(GFILE *);
int _flushbuf(int, GFILE *);
int gfflush(GFILE *);
GFILE *gfopen(const char *, const char *);
int gfclose(GFILE *);
int _populate(int, int, int, char *, GFILE *);


int ggetchar(void);
int gputchar(char);
int ggetc(GFILE *);
int gfgetc(GFILE *);
int gputc(int, GFILE *); 
int gfputc(int, GFILE *); 
ssize_t ggetline (char **, size_t *, GFILE *);
ssize_t ggetdelim(char **, size_t *, char, GFILE *);
int _gprintf_inter(GFILE *, char *, size_t, int, char *, va_list);
int gprintf(char *, ...);
int gsprintf(char *, char *, ...);
int gsnprintf(char *, size_t, char *, ...);
int gdprintf(int, char *, ...);
int gfprintf(GFILE *, char *, ...);
int gvprintf(char *, va_list);
int gvsprintf(char *, char *, va_list);
int gvsnprintf(char *, size_t, char *, va_list);
int gvdprintf(int, char *, va_list);
int gvfprintf(GFILE *, char *, va_list);
size_t gfread(void *, size_t, size_t, GFILE *);
size_t gfwrite(const void *, size_t, size_t, GFILE *);
int gfeof(GFILE *);
int gferror(GFILE *);
int gfileno(GFILE *);

size_t uint2str(char *, size_t, int);
size_t flt2str(char *, double);
size_t int2str(char *, long long, int);
size_t int2str_inter(char *, long long, int); 

size_t flt2str(char *, double);


#define gstdin  (&_IO_stream[0])
#define gstdout (&_IO_stream[1])
#define gstderr (&_IO_stream[2])

GFILE _IO_stream[FOPEN_MAX] = {
	{ 0, _READ, NULL, NULL, NULL, 0},
	{ 1, _WRITE, NULL, NULL, NULL, 0},
	{ 2, _WRITE | _UNBUF, NULL, NULL, NULL, 0}
};

int gferror(GFILE *fp)
{
	if ( (fp->flags & _ERR) != 0 )
		return 0;
	return 1;
} 

int gfeof(GFILE *fp)
{
	if ( (fp->flags & _EOF) != 0 )
		return 0;
	return 1;
}

int gfileno(GFILE *fp)
{
	return fp->fd;
}

int ggetc(GFILE *fp)
{
	if ((--(fp)->len >= 0))
		return (unsigned char) *(fp)->rp++;
	return _fillbuf(fp);
}

int gfgetc(GFILE *fp)
{
	return ggetc(fp);
}

int gputc(int x, GFILE *fp)
{
	if ((--(fp)->len >= 0))
		return *(fp)->rp++ = x;
	return _flushbuf(x, fp);
}

int gfputc(int x, GFILE *fp)
{
	return gputc(x, fp);
}

int getchar(void)
{
	return ggetc(gstdin);
}

int putchar(int x)
{
	return gputc(x, gstdout);
}

GFILE *gfopen(const char * restrict name, const char * restrict mode)
{
	int fd;
	GFILE *fp;
	int perms = 0; //  not yet used
	const char *p = mode;
	int oflags = 4242;
	int iflags = 4242;
	int seek = -1;
	
	for (fp = _IO_stream; fp < _IO_stream + FOPEN_MAX; fp++)
		if ((fp->flags & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _IO_stream + FOPEN_MAX)
		return NULL;

	while (*p)
	{
		switch (*p++)
		{
			case 'r': 
				oflags = O_RDONLY;
				iflags = _READ;
				switch (*p)
				{
					case '+':
						oflags = O_RDWR;
						iflags = _READ | _WRITE;
						break;
					default:
						break;
				}
				break;
			case 'w':
				oflags = O_TRUNC | O_CREAT;
				iflags = _WRITE;
				switch (*p)
				{
					case '+':
						oflags = O_TRUNC | O_CREAT | O_RDWR;
						iflags = _WRITE;			
						break;
					default:
						break;
				}
				break;
			case 'a':
				oflags = O_CREAT | O_APPEND;
				iflags = _WRITE;
				switch (*p)
				{
					case '+':
						oflags = O_CREAT | O_APPEND | O_RDWR;
						iflags = _READ | _WRITE;
						break;
					default:
						break;
				}
				seek = SEEK_END;
				break;
			default:
				if ( iflags == 4242 || oflags == 4242 )
					return NULL;
				break;
		}
	} 

	if ((fd = open(name, oflags, perms)) == -1)
		return NULL;

	if (seek == SEEK_END)
		lseek(fd, 0L, seek);
	
	fp->len = 0;
	fp->rp = fp->buf = NULL;
	fp->flags = iflags;
	fp->fd = fd;

	return fp;
}

int _fillbuf(GFILE *fp)
{
	int bufsize = 0;
	static char buffer[BUFSIZ] = { 0 };
	if ((fp->flags & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;
	if (fp->buf == NULL)
		fp->buf = buffer;
	fp->rp = fp->buf;
	fp->len = read(fp->fd, fp->rp, bufsize);

	if (--fp->len < 0) {
		if (fp->len == -1)
			fp->flags |= _EOF;
		else
			fp->flags |= _ERR;
		fp->len = 0;
		gfflush(NULL);
		return EOF;
	}

	return (unsigned char) *fp->rp++;
}

int _flushbuf(int x, GFILE *fp)
{
	int bufsize;
	static char buffer[BUFSIZ] = { 0 };
	bufsize = (fp->flags & _UNBUF) ? 1 : BUFSIZ;

	if (fp->buf == NULL)
	{
		fp->buf = buffer;
		fp->lp = fp->rp = fp->buf;
	}
	/*
	if (fp->fd == 1)
	{
		if ( x == '\n')
		{ 
			ret = write(fp->fd, fp->lp, fp->lp - fp->rp);
			fp->lp = fp->rp;
			fp->rp = fp->buf;
			fp->len = bufsize - 1 - ret; 
			*fp->rp++ = (char) x;
			return x;
		}
	}else 
	*/
	else if (write(fp->fd, fp->buf, fp->rp - fp->buf) < 0)
	{ 
		fp->flags |= _ERR;
		return EOF; 
	}

	fp->rp = fp->buf;
	fp->len = bufsize - 1; 
	if (x != EOF)
		*fp->rp++ = (char) x;
	return x;
}

int gfflush(GFILE *fp)
{
	int ret = 0; 
	size_t i = 0; 
	/* fflush(NULL) flushes all fd */
	if ( fp == NULL )
	{
		for ( fp = gstdout; i < FOPEN_MAX ; ++fp, ++i) 
			if ( fp->buf != NULL ) 
				ret = _flushbuf(EOF, fp); 
		
	}
	else if (fp->flags & _WRITE)
		ret = _flushbuf(EOF, fp);

	fp->rp = fp->buf;
	fp->len = (fp->flags & _UNBUF) ? 1 : BUFSIZ; 
	fp->buf = NULL;
	return ret;
}

int gfclose(GFILE *fp)
{
	int ret = 0;
	if (fp != NULL )
	{
		if ((ret = gfflush(fp)) != EOF)
		{
			fp->rp = fp->buf = NULL;
			fp->len = 0;
			fp->flags &= ~(_READ | _WRITE);
			close(fp->fd);
		}
	}
	return ret;
}

char *gfgets(char * restrict s, int n, GFILE * restrict iop)
{
	register int c;
	register char *cs;
	cs = s;
	while (--n > 0 && (c = ggetc(iop)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs = '\0';
	return (c == EOF && cs == s) ? NULL : s;
}

int gfputs(char * restrict s, GFILE * restrict iop)
{
	int c;
	while ((c = *s++))
		gputc(c, iop);
	return gferror(iop) ? EOF : 0;
}

/* Printf family (variadic and formatted) */
int _populate(int incr, int x, int flag, char *s, GFILE *fp)
{
	/* flag == 1 == sprintf */
	/* flag == 2 == snprintf */
	/* flag == 0 == printf, vprintf, dprintf etc  */

	if ( flag > 0 )
		*s = x;
	else
		gputc(x, fp);
	return incr + 1;
}

int _gprintf_inter(GFILE *fp, char *str, size_t lim, int flag, char *fmt, va_list ap)
{
	char *p = NULL;
	size_t i = 0;
	size_t bound = BUFSIZ;
	int base = 10;

	/* Hold comverted numerical strings */
	char converted[BUFSIZ] = { 0 };
	int convlen = 0;
	int j = 0;

	/* data types */
	int cval = 0;
	char *sval = NULL;
	size_t zuval = 0;
	long long lval = 0;
	long double fval = 0;

	/* float precision */
	//int precision = 6;
	int precision = 40;

	

	if ( flag == 2 ) 	/* snprintf */
		bound = lim;

	for (p = fmt; *p && i < bound; p++) 
	{
		if (*p != '%')
		{
			i = _populate(i, *p, flag, str++, fp);
			continue;
		}
		switch (*++p)
		{
			case 'c':
				cval = va_arg(ap, int);
				goto character; 
			case 's':
				sval = va_arg(ap, char *);
				goto string; 
			case 'o':
				base = 8;
				lval = va_arg(ap, int);
				goto integer; 
			case 'd':
				lval = va_arg(ap, int);
				goto integer;
			case 'x':
				base = 16;
				lval = va_arg(ap, int);
				goto integer;
			case 'f':
				fval = va_arg(ap, double);
				goto floating;
			case 'L':
				switch (*++p)
				{
					case 'f':
						fval = 0;
						fval = va_arg(ap, long double);
						goto floating;
				}
				break;
			case 'l':
				switch (*++p)
				{
					case 'd':
						lval = va_arg(ap, long);
						goto integer;
					case 'l':
						switch (*++p)
						{
							case 'd':
								lval = va_arg(ap, long long);
								goto integer;
						}
						break;
					case 'f':
						fval = 0;
						fval = va_arg(ap, double);
						goto floating;
					default:
						break;
				}
				break;
			case 'z':
				switch (*++p)
				{
					case 'u':
						zuval = va_arg(ap, size_t);
						goto uinteger;
				}
				break;
			default:
				i = _populate(i, *p, flag, str++, fp);
				break;
			string:
				for (; *sval; sval++, ++i)
					i = _populate(i, *sval, flag, str++, fp);
				break;
			character:
				i = _populate(i, cval, flag, str++, fp);
				break;
			integer:
				memset(converted, 0, 100);
				convlen = int2str(converted, lval, base);
				for ( j = 0 ; j < convlen ; ++j)
					i = _populate(i, converted[j], flag, str++, fp);
				base = 10;
				break;
			uinteger:
				convlen = int2str(converted, zuval, base);
				for ( j = 0 ; j < convlen ; ++j)
					i = _populate(i, converted[j], flag, str++, fp);
				break;
			floating:
				convlen = flt2str(converted, fval);
				for ( j = 0 ; convlen-- ; ++j)
				{
					if (converted[j] == '.')
						if ( convlen > precision)
							convlen = precision;
					i = _populate(i, converted[j], flag, str++, fp);
				}
				//memset(converted, 0, 100);
				break;
		}
	}

	if ( flag > 0 )
		_populate(i, '\0', flag, str, fp); /* don't incr for '\0' */

	if (flag == 0)
		gfflush(NULL);

	return i;
}

int gprintf(char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(gstdout, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gsprintf(char *str, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(NULL, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gsnprintf(char *str, size_t lim, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(NULL, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gdprintf(int fd, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(gstdin + fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gvprintf(char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(gstdout, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsprintf(char *str, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(NULL, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsnprintf(char *str, size_t lim, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(NULL, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvdprintf(int fd, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(gstdin + fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gfprintf(GFILE *stream, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = _gprintf_inter(stream, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvfprintf(GFILE *stream, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = _gprintf_inter(stream, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

size_t gfread(void *ptr, size_t size, size_t nmemb, GFILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = read(fp->fd, ptr, request);
	return ret / size;
}

size_t gfwrite(const void *ptr, size_t size, size_t nmemb, GFILE *fp)
{
	size_t request = size * nmemb;
	size_t ret = write(fp->fd, ptr, request);
	return ret / size;
}

size_t __uint2str(char *s, size_t n, int base)
{
	static size_t i = 0; 
	
//	if ( n == 0 )
//	{
//		s[i] = '0';
	//	return 1;
	//} 
	if (n / base )
	{
		//i = 0;
		__uint2str(s, n / base, base);
	} 
	if (n % base + '0' > '9')
		s[i] = (n % base + '0' + 39);
	else 
		s[i++] = (n % base + '0'); 
	return ++i;
}
size_t uint2str(char *s, size_t n, int base)
{ 
	return __uint2str(s, n / base, base);
}

size_t __int2str(char *s, long long n, int base)
{
	static size_t i = 0; 
	if (n / base )
	{
	      i = 0;
	       __int2str(s, n / base, base); 
	}
	if (n % base + '0' > '9')
		s[i] = (n % base + '0' + 39);
	else
		s[i] = (n % base + '0'); 

	return ++i;
}

size_t int2str(char *s, long long n, int base)
{ 
	int toggle = 0;
	int convtab[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	if ( n < 0 )
	{
		n = -n;
		s[0] = '-';
		toggle = 1;
	}
	if ( n <10 )
	{
		s[toggle] = convtab[n];
		return toggle + 1;
	}
	
	size_t ret = __int2str(s + toggle, n, base) + toggle;
	
	//while (isdigit( s[j]) == 0 )
	//	++j;
	//memmove(s, s+j, ret - j);

	return ret;
}

size_t flt2str(char *s, double flt)
{
	size_t i = 0; 
	long long real = flt;
	double imag = flt - real; 
	int prec = 20;
	int convtab[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	
	
	if ( real != 0) 
		i = int2str(s, real, 10); 
	else
		s[i++] = '0';

	s[i++] = '.';

	if ( imag > 0 )
	{
		while ( imag > 0 && --prec)
		{
			imag *= 10;
			real = imag;
			imag -= real;
			s[i++] = convtab[real];
			real = 0;
		}
	}
	else 
	{
		memset(s + i, '0', 20);
		i += 20;
	}
	return i;
}

ssize_t ggetdelim(char **lineptr, size_t *n, char delim, GFILE *fp)
{
        size_t len = 0;
        char *pos = NULL;
        ssize_t ret = -1;
        size_t chunk = BUFSIZ;
        int c = 0;

        if (!*lineptr)
        {
                *n = chunk;
                if (!(*lineptr = malloc (chunk)))
                        return -1;
        }

        len = *n;
        pos = *lineptr;

        for ( ; c != delim ;len--, pos++)
        {
                read (fp->fd, &c, 1);
                if (c == 0 || c == -1)
                        c = EOF;

                if (len == 0)
                {
                        *n += chunk;
                        len = chunk;
                        if (!(*lineptr = realloc (*lineptr, *n)))
                                return ret;
                        pos = *lineptr;
                }

                if (c == EOF )
                {
                        if (pos == *lineptr)
                                return ret;
                        else
                                break;
                }
                *pos = c;
        }

        *pos = '\0';

        ret = pos - (*lineptr);
        return ret;
}

ssize_t ggetline(char **lineptr, size_t *n, GFILE *fp)
{
        return ggetdelim(lineptr, n, '\n', fp);
}
