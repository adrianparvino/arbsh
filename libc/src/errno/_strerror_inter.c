#include <gerrno.h>

/* An incomplete list, use the macros from ../include/gerrno.h to complete this */

struct _messages {
	int macro;
	char *errstr;
} *_messages = {
	{ E2BIG, "Argument list too long." },
	{ EACCES, "Permission denied." },
	{ EADDRINUSE, "Address in use." },
	{ EADDRNOTAVAIL, "Address not available." },
	{ EAFNOSUPPORT, "Address family not supported." },
	{ EAGAIN, "Resource unavailable, try again ...." },
	{ EALREADY, "Connection already in progress." },
	{ EBADMSG, "Bad message." },
};



