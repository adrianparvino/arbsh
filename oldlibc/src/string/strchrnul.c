#include <gstddef.h>
#include <gstring.h>

/* Copyright (c) 2017, Iain Hill */

char *gstrchrnul(const char *s, int c)
{
	for ( ; *s != '\0'; s++)
		if(*s == c)
			return (char*)s;

	return (char*)s;
}

