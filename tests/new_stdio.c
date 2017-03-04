#include "fcntl.h" 
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

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
int gputc(int, GFILE *); 
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

int gputc(int x, GFILE *fp)
{
	if ((--(fp)->len >= 0))
		return *(fp)->rp++ = x;
	return _flushbuf(x, fp);
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
	int perms = 0666;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _IO_stream; fp < _IO_stream + FOPEN_MAX; fp++)
		if ((fp->flags & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _IO_stream + FOPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, perms);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, perms);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0); 

	if (fd == -1)
		return NULL; 
	
	fp->len = 0;
	fp->rp = fp->buf = NULL;
	fp->flags = (*mode == 'r') ? _READ : _WRITE;
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
				convlen = int2str(converted, lval, base);
				for ( j = 0 ; j < convlen ; ++j)
					i = _populate(i, converted[j], flag, str++, fp);
				base = 10;
				break;
			uinteger:
				convlen = uint2str(converted, zuval, base);
				for ( j = 0 ; j < convlen ; ++j)
					i = _populate(i, converted[j], flag, str++, fp);
				break;
			floating: 
				convlen = flt2str(converted, fval);
				for ( j = 0 ; convlen-- ; ++j)
				{
					if (converted[j] == '.')
						if ( convlen > 6)
							convlen = 6;
					i = _populate(i, converted[j], flag, str++, fp);
				}
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

size_t uint2str(char *s, size_t n, int base)
{
	static size_t i = 0; 
	if ( n == 0 )
	{
		s[i] = '0';
		return 1;
	} 
	if (n / base )
	{
		i = 0;
		uint2str(s, n / base, base);
	} 
	if (n % base + '0' > '9')
		s[i] = (n % base + '0' + 39);
	else 
		s[i] = (n % base + '0'); 
	return ++i;
}

size_t __int2str(char *s, long long n, int base)
{
	static size_t i = 0;
	if ( n == 0 )
	{
		s[i] = '0';
		return 1;
	}
	if (n / base )
	{
	       i = 0;
	       int2str(s, n / base, base);
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
	if ( n < 0 )
	{
		n = -n;
		s[0] = '-';
		toggle = 1;
	}
	return  __int2str(s + toggle, n, base) + toggle;
}

size_t flt2str(char *s, double n) 
{
	static double PRECISION = 0.00000000000001; 
	size_t i = 0;
	
	int digit, m, m1;
	char *c = s;
	int neg = (n < 0);
	double weight = 0;

	if (n == 0.0) {
		s[i++] = '0';
		s[i++] = 0;
	} else {
		if (neg)
			n = -n;
	
		m = log10(n);
		
		if (neg)
		{
			*(c++) = '-';
			i++;
		} 
		if (m < 1.0) {
			m = 0;
		}

		while (n > PRECISION || m >= 0)
		{
			weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
				i++;
			}
			if (m == 0 && n > 0)
				*(c++) = '.';
			m--;
		}
		*(c) = '\0';
	}
	return i;
}


void simple_copy(char *src, char *dest)
{
	int c = 0;
	GFILE *fpsrc = gfopen(src, "r");
	GFILE *fpdest = gfopen(dest, "w");
	while ((c = ggetc(fpsrc)) != EOF) 
		gputc(c, fpdest);
	gfclose(fpsrc);
	gfclose(fpdest);
}

void simplecat(char *file)
{
	int c = 0;
	GFILE *fp = gfopen(file, "r");
	while ((c = ggetc(fp)) != EOF)
		gputc(c, gstdout);
	gfclose(fp);
}

void testgvprintf(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	gvprintf(fmt, args);
	va_end(args);
}

int main(int argc, char *argv[])
{
	
	char string[10] = { 'h', 'e', 'l', 'l', 'o', '\0' };
	size_t zutest = 1234567;
	int dtest = -9879871;
	char string1[1000] = { 0 };
	long ltest = 23459999;
	double ftest = 3123.21317892345;
	double ftest2 = 0.202309823709099;
	char *format = "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld==%f==%lf\n";

	if ( argc == 2 ) 
		simplecat(argv[1]); 
	else if ( argc == 3) 
		simple_copy(argv[1], argv[2]); 
	else {

		gfprintf(gstdout, "decimal value of 987654         %d\n", 987654);
		gfprintf(gstdout, "octal value of 987654           %o\n", 987654);
		gfprintf(gstdout, "hexadecimal value of 987654     %x\n", 987654);
		gfprintf(gstdout, "The string literal \"987654\"     %s\n", "987654");
		gfprintf(gstdout, "decimal value of -987654        %d\n", -987654);

		
		gdprintf(1, "decimal value of 987654         %d\n", 987654);
		gdprintf(1, "octal value of 987654           %o\n", 987654);
		gdprintf(1, "hexadecimal value of 987654     %x\n", 987654);
		gdprintf(1, "The string literal \"987654\"     %s\n", "987654");
		gdprintf(1, "decimal value of -987654        %d\n", -987654);

	
		gprintf("gfprintf:\n");
		gfprintf(gstderr, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

		gprintf("gdprintf:\n");
		gdprintf(2, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);
		gprintf("gprintf:\n");
		gprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);
		gprintf("gsprintf:\n");
		gsprintf(string1, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

		gprintf("gvprintf:\n");
		testgvprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

	}
	return 0;
}





