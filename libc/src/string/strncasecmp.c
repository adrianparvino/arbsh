#include <gstddef.h>
#include <gctype.h>
#include <gstring.h>
#include <ctype.h>

int gstrncasecmp(const char *s, const char *t, size_t n)
{
	int s_bis, t_bis;
	size_t i = 0;

        while (*s && *t && i++ < n)
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

