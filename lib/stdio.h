
#define GBUFSIZ 4096
#define IRCBUFSIZ GBUFSIZ

#include <stddef.h>
#include <stdarg.h>

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


int gprintf(char *fmt, ...)
{
	va_list ap;
	char *p = NULL;
        char *sval = NULL;
	size_t i = 0; /* this should be an int according to the IEEE */
	size_t zuval = 0;
	char zuhold[1025];
	size_t zulen = 0;
	int dval = 0;
	char dhold[1025];
	size_t dlen = 0;
	//char *out;
	char out[1025] = { 0 };

//	if ( flag == 0 ) // normal printf 
//		out = malloc(1025); 
//	if ( flag == 1) //sprintf 
//		out = str;

	va_start(ap, fmt);

	for (p = fmt; *p; p++) 
	{
		if (*p != '%')
		{
			out[i++] = *p;
			continue;
		}
		switch (*++p)
		{
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++) 
					out[i++] = *sval; 
				break;
			case 'd': 
				dval = va_arg(ap, int);
				dlen = intostrbase(dhold, dval, 10);
				memcpy(out + i, dhold, dlen);
				i +=dlen;
				break;
			case 'z':
				switch (*++p)
				{ 
					case 'u':
						zuval = va_arg(ap, size_t);
						zulen = uintostrbase(zuhold, zuval, 10);
						memcpy(out + i, zuhold, zulen);
						i += zulen;
					default:
						break;
				}
				break;
			default:
				out[i++] = *p;
				break;
		}
	}
	va_end(ap);

	//if ( flag == 0 )
		write(1, out, i);

	return i;
}

//int gprintf(char *fmt, ...)
//{
//	size_t ret  = 0;
//	ret = gprintf_inter(fmt, ...);
//	return ret;
//}

//int gsprintf(char *str, char *fmt, ...)
//{
//	size_t ret = 0;
//	ret = gprintf_inter(str, 1, fmt);
//	return ret;
//}

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


