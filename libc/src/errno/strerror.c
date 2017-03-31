#include <gerrno.h>

/* x86 ( incomplete )  */
char *_messages[125] = {
	"\0",					/* (not used)	0	*/
	"Operation not permitted.\0",		/* EPERM	1	*/
	"No such file or directory.\0",		/* ENOENT	2	*/
	"No such process.\0",			/* ESRCH	3	*/
	"Interrupted function.\0",		/* EINTR	4	*/
	"\0",					/* ?		5	*/
	"No such device or address.\0",		/* ENXTA	6	*/
	"Argument list too long.\0",		/* E2BIG	7	*/
	"Executable file format error.\0",	/* ENOEXEC	8	*/
	"\0",					/* ?		9	*/
	"No child processes.\0",		/* ECHILD	10	*/
	"Resource unavailable, try again.\0", 	/* EAGAIN	11	*/
	"Not enough space.\0", 			/* ENOMEM	12	*/
	"Permission denied.\0",			/* EACCESS	13	*/
	"Bad address.\0",			/* EFAULT	14	*/
	"\0",					/* ?		15	*/
	"Device or resource busy.\0",		/* EBUSY	16	*/
	"File exists.\0",			/* EEXIST	17	*/
	"Cross-device link.\0",			/* EXDEV	18	*/
	"No such device.\0",			/* ENODEV	19	*/
	"Not a directory.\0",			/* ENOTDIR	20	*/
	"Is a directory.\0",			/* EISDIR	21	*/
	"Invalid argument.\0",			/* EINVAL	22	*/
	"Too many files open in system.\0",	/* ENFILE	23	*/
	"Too many open files.\0",		/* EMFILE	24	*/
	"Inappropriate I/O control operation.\0",/*ENOTTY	25	*/
	"Text file busy.\0",			/* ETXTBSY	26	*/
	"File too large.\0",			/* EFBIG	27	*/
	"No space left on device.\0",		/* ENOSPC	28	*/
	"Invalid seek.\0",			/* ESPIPE	29	*/
	"Read-only file system.\0",		/* EROFS	30	*/
	"Too many links.\0",			/* EMLINK	31	*/
	"Broken pipe.\0",			/* EPIPE	32	*/
	"Mathematics argument out of doma.\0",	/* EDOM		33	*/
	"Result too large.\0",			/* ERANGE	34	*/
	"\0"					/* ?		35	*/
	"Filename too long.\0",			/* ENAMETOOLONG	36	*/
	"No locks available.\0",		/* ENOLCK	37	*/
	"Function not supported.\0",		/* ENOSYS	38	*/
	"Directory not empty.\0",		/* ENOTEMPTY	39	*/
	"Too many levels of symbolic links.\0",	/* ELOOP	40	*/
	"\0",					/* ?		41	*/
	"No message of the desired type.\0",	/* ENOMSG	42	*/
	"Identifier removed.\0",		/* EIDRM	43	*/ 
	"\0",					/* ? 		44	*/
	"\0",					/* ? 		45	*/
	"\0",					/* ? 		46	*/
	"\0",					/* ?		47	*/
	"\0",					/* ? 		48	*/
	"\0",					/* ?		49	*/
	"\0",					/* ?		50	*/
	"\0",					/* ? 		51	*/
	"\0",					/* ?		52	*/
	"\0",					/* ? 		53	*/
	"\0",					/* ?		54	*/
	"\0",					/* ? 		55	*/
	"Not a STREAM.\0",			/* ENOSTR	60	*/
	"No msg is avail on STREAM head.",	/* ENODATA	61	*/
	"Stream ioctl() timeout.",		/* ETIME	62	*/
	"No STREAM resources.",			/* ENOSR	63	*/
	"\0",					/* ?		64	*/
	"\0",					/* ?		65	*/
	"\0",					/* ? 		66	*/
	"Reserved.",				/* ENOLINK	67	*/
	"\0",					/* ?		68	*/
	"\0",					/* ? 		69	*/
	"\0",					/* ?		70	*/
	"Protocol error.",			/* EPROTO	71	*/
	"Reserved.",				/* EMULTIHOP	72	*/
	"\0",					/* ?		73	*/
	"Bad message.",				/* EBADMSG	74	*/
	"Val too large to be stored in data type.",/* EOVERFLOW	75	*/
	"\0",					/* ?		76	*/
	"\0",					/* ?		77	*/
	"\0",					/* ? 		78	*/
	"\0",					/* ?		79	*/
	"\0",					/* ? 		80	*/
	"\0",					/* ?		81	*/
	"\0",					/* ?		82	*/
	"\0",					/* ? 		83	*/
	"Illegal byte sequence.",		/* EILSEQ	84	*/
	"\0",					/* ?		85	*/
	"\0",					/* ?		86	*/
	"\0",					/* ?		87	*/
	"Not a socket.",			/* ENOTSOCK	88	*/
	"Destination address required.",	/* EDESTADDRREQ	89	*/
	"Message too large.",			/* EMSGSIZE	90	*/
	"Protocol wrong type for socket.",	/* EPROTOTYPE	91	*/
	"Protocol not available.",		/* ENOPROTOOPT	92	*/
	
};


char *gstrerror(int errnum)
{
	return _messages[errnum];
}
