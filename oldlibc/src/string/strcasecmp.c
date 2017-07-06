#include <gstddef.h>
#include <gctype.h>
#include <gstring.h>
#include <gctype.h>

/* Copyright (c) 2017, Iain Hill */

int gstrcasecmp(const char *s, const char *t)
{
	int s_bis, t_bis;

        while (*s && *t)
	{
		s_bis = gtolower(*s);
		t_bis = gtolower(*t);

		if (s_bis == t_bis) {
			if (*s == '\0')
				return 0;
			s++;
			t++;
		}
		else
			break;

	}
        return s_bis - t_bis;
}

