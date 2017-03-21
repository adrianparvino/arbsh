#include <gstddef.h>
#include <gctype.h>
#include <gstring.h>

int gstrcasecmp(const char *s, const char *t)
{
	int s_bis, t_bis;

        while (*s && *t)
	{
		s_bis = tolower(*s);
		t_bis = tolower(*t);

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

