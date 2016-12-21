
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
	size_t i = 0;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) 
	{
		if (*p != '%')
		{
			gputchar(*p);
			++i;
			continue;
		}
		switch (*++p)
		{
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
				{
					gputchar(*sval);
					++i;
				}
				break;
			default:
				gputchar(*p);
				++i;
				break;
		}
	}
	va_end(ap);
	return i;
}

int gsprintf(char *str, char *fmt, ...)
{
        va_list ap;
        char *p = NULL;
	char *sval = NULL;
	size_t i = 0; 

        va_start(ap, fmt);
	
        for (p = fmt; *p ; p++)
        {
                if (*p != '%')
                {
			str[i++] = *p; 
                        continue;
                }
		
                switch (*++p)
                { 
                        case 's': 
				sval = va_arg(ap, char *);
                                for (; sval && *sval; sval++)
				{ 
					str[i++] = *sval;
					str[i] = 0;
				
				} 
                                break;
                }
		
        }
        va_end(ap);
	return i;
}

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


