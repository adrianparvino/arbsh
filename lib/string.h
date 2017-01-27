size_t gstrlen(const char *); 
int gstrcmp(char *, char *);
char *gstrchr(const char *, int); 
char *gstrcpy(char *, const char *);
char *gstrncpy(char *, const char *, size_t);
char *gstrtok(char *, const char *);
size_t gstrspn(const char *, const char *);
void* gmemset(void *, int, size_t);
void* gmemcpy(void*, const void*, size_t) ;
void *gmemmove(void *, const void *, size_t);
char *gstrdup(char *);

size_t gstrlen(const char *s)
{
	size_t j = 0;
	while ( s[j] != '\0' )
		++j;
	return j;
} 

int gstrcmp(char *s, char *t)
{
        for ( ; *s == *t; s++, t++)
                if (*s == '\0')
                        return 0;
        return *s - *t;
}

char *gstrchr(const char *s, int c)
{ 
	for ( ; *s != c; s++)
		if (*s == '\0')
			return 0;
	return (char *)s;
}

char *gstrcpy(char *s, const char *t)
{ 
	for(;(*s = *t) != '\0'; s++, t++) 
		; 
	return s;
} 

char *gstrncpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	for (; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

char *gstrtok(char *s, const char *delim)
{

        char *token;
        char *span;
        static char *last;

        int c;
	int hold;

        if (s == NULL) 
	{
		s = last;
		if (s == NULL)
        	       	return NULL; 
	}


        c = *s++;
	
        for (span = (char *)delim; (hold = *span++) != 0;) 
	{
                if (c == hold)
                {
                        c = *s++;
                        span = (char *)delim;
                }
        }

        if (c == 0) 
                return (last = NULL);
	
	token = s - 1; 	
    
        while ( 1 ) 
	{
                c = *s++;
                span = (char *)delim;
                do {
                        if ((hold = *span++) == c) 
			{
                                if (c == 0)
                                        s = NULL;
                                else
                                        s[-1] = 0;
                                last = s;
                                return (token);
                        }
                } while (hold != 0);
        }
} 

size_t gstrspn(const char *s1, const char *s2)
{
	size_t i = 0;
	size_t j = 9;

	for ( ; *(s1+i) ; i++)
	{
		for (j = 0 ; *(s2+j) ; j++) 
			if(*(s1+i) == *(s2+j))
				break; /* Found a match. */ 
		if (!*(s2+j))
			return i; /* No match found. */ 
	}
	return i;
}

void* gmemset(void *s, int c, size_t len)
{
	unsigned char *dst = s;
	for (;len > 0; dst++,len--)
		*dst = (unsigned char) c;
	return s;
}

/*
void *gmemset(void *s, int c, size_t len)
{ 
	if ( len )
	{
		*((char *)s) = (char)c;
		gmemset(++s, c, --len);
	} 
	return s;
}
*/
/*
void* gmemcpy(void* destination, const void* source, size_t len)
{ 
	if ( len )
	{
		*(char *)destination = *(char *)source;
		gmemcpy(++destination, ++source, --len);
	}
	return destination;
} 
*/


void* gmemcpy(void* destination, const void* source, size_t len)
{
	size_t i = 0;
	char *d = destination;
	const char *s = source;
	for (; i < len; i++) 
		d[i] = s[i]; 
	return destination;
} 

void *gmemmove(void *to, const void *from, size_t size)
{
	unsigned char *p1;
	const unsigned char *p2;

	p1 = (unsigned char *) to;
	p2 = (const unsigned char *) from;

	p2 = p2 + size;

	// Check if there is an overlap or not.
	while (p2 != from && --p2 != to)
		;


	if (p2 != from)
	{ 	
		p2 = (const unsigned char *) from;
		p2 = p2 + size;
		p1 = p1 + size;

		while (size-- != 0)
		{
			*--p1 = *--p2;
		}
	}
	else
	{ 
		while (size-- != 0)
		{
			*p1++ = *p2++;
		}
	}

	return(to);
}

char *gstrdup(char *s)
{
	char *ret;
	size_t len = gstrlen(s) + 1;
	ret = malloc(len);
	gmemcpy(ret, s, len);
	return ret;
}
