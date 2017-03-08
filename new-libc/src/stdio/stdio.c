#include <gstdio.h> 

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

size_t __uint2str(char *s, size_t n, int base)
{
	static size_t i = 0; 
	if (n / base )
	{ 
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
