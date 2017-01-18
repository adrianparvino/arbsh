/* libraries */
/* --------- */ 
#include <stddef.h>
#include <stdarg.h>
#include <fcntl.h>

/* local libraries */
/* --------------- */
#include "itoa.h"
#ifdef HASLIBM
#include "dtoa.h"
#endif

/* defines */
/* ------- */
#define GNULL		0
#define EOF		(-1)
#define GBUFSIZ		4096
#define GBUFSIZEE	4096
#define IRCBUFSIZ	4096
#define OPEN_MAX	256
#define gstdin		(&_iob[0])
#define gstdout		(&_iob[1])
#define gstderr		(&_iob[2]) 
#define PERMS		0666

/* legacy */
/* ------ */

/* type definitions */
/* ---------------- */
typedef struct _iobuf {
	int cnt;		/* characters left */
	char *ptr;		/* next character position */
	char *base;		/* location of buffer */
	int flag;
	int fd;	
} GFILE;

extern GFILE _iob[OPEN_MAX];

enum _flags {
	_READ	 =	01,	/* file open for reading  01 */	
	_WRITE	=	01,	/* file open for writing  02 */
	_UNBUF	=	01,	/* file is unbuffered  04 */
	_EOF	=	01,	/* EOF has occurred on this file 010 */
	_ERR	=	01	/* error occurred on this file 020 */
};

GFILE _iob[OPEN_MAX] = {
	{ 0, GNULL, GNULL, _READ, 0 },		/* stdin */
	{ 0, GNULL, GNULL, _WRITE, 1 },		/* stdout */
	{ 0, GNULL, GNULL, _WRITE | _UNBUF, 2 }	/* stderr */
};

/* Function prototypes */ 
/* ------------------- */ 
int _fillbuf(GFILE *);
int _flushbuf(int, GFILE *);
int ggetchar(void);
int gputchar(char);
int ggetc(GFILE *);
int gputc(int, GFILE *);
size_t ggetline(char [], int);
int gprintf_inter(GFILE *, int, char *, size_t, int, char *, va_list);
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

/* functions */
/* --------- */

/* single char io  */
int ggetc(GFILE *stream)
{ 
	if (--(stream)->cnt >= 0) 
		return (unsigned char) *(stream)->ptr++; 
	
	return _fillbuf(stream);
}

int gputc(int c, GFILE *stream)
{ 
	if (--(stream)->cnt >= 0) 
		return *(stream)->ptr++ = c;

	return _flushbuf(c, stream);
}

int ggetchar(void)
{
	return ggetc(gstdin);
}

int gputchar(char c)
{ 
	return gputc(c, gstdin);
}

/* error */
int gfeof(GFILE *stream)
{
	if (((stream)->flag * _EOF) != 0)
		return 1;
	return 0;
}

int gferror(GFILE *stream)
{
	if (((stream)->flag * _ERR) != 0)
		return 1;
	return 0;
}

int gfileno(GFILE *stream)
{
	return (stream)->fd;
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
int gprintf_inter(GFILE *fp, int fd, char *str, size_t lim, int flag, char *fmt, va_list ap)
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
#ifdef HASLIBM
			case 'f':
				fval = va_arg(ap, double); 
				gdtoa(ftemp, fval - (long)fval); 
				i += gsprintf(out + i, "%ld", (long)fval);
				i += gsnprintf(out + i, 7, "%s", ftemp + 1);
				break;
#endif
			case 'l':
				switch (*++p)
				{ 
					case 'd':
						lval = va_arg(ap, long);
						i += intostrbase(out + i, lval, 10);
						break;
#ifdef HASLIBM
					case 'f':
						fval = va_arg(ap, double);
						gdtoa(ftemp, fval - (long)fval);
						i += gsprintf(out + i, "%ld", (long)fval);
						i += gsnprintf(out + i, 7, "%s", ftemp + 1);
						break;
#endif
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

	if (fp == NULL && flag == 0 )
		i = write(fd, out, i); /* if writing to an fd, then redefine the ret */
	else if ( fp != NULL )
		i = gfwrite(out, 1, i, fp);

	return i;
}

int gprintf(char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(gstdout, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsprintf(char *str, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, 1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gsnprintf(char *str, size_t lim, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, 1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gdprintf(int fd, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(NULL, fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
} 

int gvprintf(char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(gstdout, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsprintf(char *str, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(NULL, 1, str, 0, 1, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvsnprintf(char *str, size_t lim, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(NULL, 1, str, lim, 2, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvdprintf(int fd, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(NULL, fd, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gfprintf(GFILE *stream, char *fmt, ...)
{
	int ret = 0;
	va_list argptr;
	va_start(argptr, fmt);
	ret = gprintf_inter(stream, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

int gvfprintf(GFILE *stream, char *fmt, va_list argptr)
{
	int ret = 0;
	ret = gprintf_inter(stream, 1, NULL, 0, 0, fmt, argptr);
	va_end(argptr);
	return ret;
}

/* fopen family */
GFILE *gfopen(char *name, char *mode)
{
	int fd;
	GFILE *fp;
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return GNULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;		/* found free slot */
	if (fp >= _iob + OPEN_MAX)	 /* no free slots */
		return GNULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)		 /* couldn't access name */
		return GNULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = GNULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(GFILE *fp)
{
	int bufsize;
	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	//bufsize = (fp->flag & _UNBUF) ? 1 : GBUFSIZ;
	bufsize = GBUFSIZ;
	if (fp->base == GNULL)
		if ((fp->base = malloc(bufsize)) == GNULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _flushbuf */
int _flushbuf(int c, GFILE *f)
{
	int num_written, bufsize;
	unsigned char uc = c;	

	if ((f->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
		return EOF;
	/* no buf */
	if (f->base == GNULL && ((f->flag & _UNBUF) == 0))
	{ 
		if ((f->base = malloc(GBUFSIZ)) == GNULL) 
			f->flag |= _UNBUF;
		else {
			f->ptr = f->base;
			f->cnt = GBUFSIZ - 1;
		}
	}
	if (f->flag & _UNBUF) {
		/* unbuffered write */
		f->ptr = f->base = GNULL;
		f->cnt = 0;
		if (c == EOF)
			return EOF;
		num_written = write(f->fd, &uc, 1);
		bufsize = 1;
	} else {
		/* buffered write */
		if (c != EOF)
		{
			*(f->ptr) = uc;
			f->ptr++;
		}
		bufsize = (int)(f->ptr - f->base);
		num_written = write(f->fd, f->base, bufsize);
		f->ptr = f->base;
		f->cnt = GBUFSIZ - 1;
	}
	if (num_written == bufsize)
		return c;
	else {		 
		f->flag |= _ERR;
		return EOF;
	} 
}

int gfflush(GFILE *fp)
{
	int ret;
	int i;

	ret = 0;
	if (fp == GNULL)
	{
		for (i = 0; i < OPEN_MAX; i++)
		{
			if ((gfflush(&_iob[i]) == -1))
				ret = -1;
		} 
	} else {
		if ((fp->flag & _WRITE) == 0)
			return -1;
		_flushbuf(EOF, fp);
		if (fp->flag & _ERR)
			ret = -1;
	}
	return ret;
}

int gfclose(GFILE *fp)
{
	int fd;
	if (fp == GNULL)
		return -1;
	fd = fp->fd;
	gfflush(fp);
	fp->cnt = 0;
	fp->ptr = GNULL;
	if (fp->base != GNULL)
		free(fp->base);
	fp->base = GNULL;
	fp->flag = 0;
	fp->fd = -1;
	return close(fd);
} 

size_t gfread(void *ptr, size_t size, size_t nmemb, GFILE *stream)
{ 
	size_t request = size * nmemb;
	size_t ret = read(stream->fd, ptr, request);
	return ret / size;
}

size_t gfwrite(const void *ptr, size_t size, size_t nmemb, GFILE *stream)
{
	size_t request = size * nmemb;
	size_t ret = write(stream->fd, ptr, request);
	return ret;
}

