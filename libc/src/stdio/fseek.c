#include <gstdio.h>

int gfseek(FILE *fp, long offset, int whence)
{
	_flushbuf(EOF, fp);
	;// perform an lseek here
}
