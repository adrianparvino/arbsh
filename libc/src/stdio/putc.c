#include <gstdio.h> 

int gputc(int x, GFILE *fp)
{
	if ((--(fp)->len >= 0))
		return *(fp)->rp++ = x;
	return _flushbuf(x, fp);
}
