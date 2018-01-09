#include <arbprec/arbprec.h>
static int __convtab[20] = { '0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

static size_t __uint2str_inter(char *s, size_t n, int base, size_t i)
{
        if (n / base) {
                i = __uint2str_inter(s, n / base, base, i);
        }
        s[i] = __convtab[(n % base)];
        return ++i;
}

static size_t __uint2str(char *s, size_t n, int base)
{
        size_t i = 0;
        return __uint2str_inter(s, n, base, i);
}

fxdpnt *hrdware2arb(size_t a)
{

	char str[50];
	sprintf(str, "%zu", a);
	fxdpnt *ret = arb_str2fxdpnt(str);
	return ret;
}

