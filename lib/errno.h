

int *error(void);
#define errno (*error())

 
#define E2BIG 		7  	/* Argument list too long. 		*/
#define EACCES 		13  	/* Permission denied.			*/
#define EADDRINUSE 	98  	/* Address in use. 			*/
#define EADDRNOTAVAIL 	99  	/* Address not available. 		*/
#define EAFNOSUPPORT 	97  	/* Address family not supported. 	*/
#define EAGAIN 		11  	/* Resource unavailable, try again .... */
#define EALREADY 	114  	/* Connection already in progress. 	*/
/* #define EBADF *//* Bad file descriptor.				*/
#define EBADMSG 	74  	/* Bad message. 			*/
#define EBUSY 		16  	/* Device or resource busy. 		*/
/* #define ECANCELED  */  	/* Operation canceled.			*/
#define ECHILD 		10  	/* No child processes. 			*/
#define ECONNABORTED 	103  	/* Connection aborted. 			*/
#define ECONNREFUSED 	111  	/* Connection refused. 			*/
#define ECONNRESET 	104  	/* Connection reset. 			*/
/* #define EDEADLK *//* Resource deadlock would occur.			*/
#define EDESTADDRREQ 	89  	/* Destination address required. 	*/
#define EDOM 		33  	/* Mathematics argument out of doma ... */
#define EDQUOT 		122  	/* Reserved. 				*/
#define EEXIST 		17  	/* File exists. 			*/
#define EFAULT 		14  	/* Bad address. 			*/
#define EFBIG 		27  	/* File too large. 			*/
#define EHOSTUNREACH 	113  	/* Host is unreachable. 		*/
#define EIDRM 		43  	/* Identifier removed. 			*/
#define EILSEQ 		84  	/* Illegal byte sequence.		*/
#define EINPROGRESS 	115  	/* Operation in progress.		*/
#define EINTR 		4  	/* Interrupted function.		*/
#define EINVAL 		22  	/* Invalid argument.			*/
/* #define EIO *//* I/O error.						*/
#define EISCONN 	106  	/* Socket is connected.			*/
#define EISDIR 		21  	/* Is a directory.			*/
#define ELOOP 		40  	/* Too many levels of symbolic links. 	*/
#define EMFILE 		24  	/* Too many open files.			*/
#define EMLINK 		31  	/* Too many links.			*/
#define EMSGSIZE 	90  	/* Message too large.			*/
#define EMULTIHOP 	72  	/* Reserved.				*/
#define ENAMETOOLONG 	36  	/* Filename too long.			*/
#define ENETDOWN 	100  	/* Network is down.			*/
#define ENETRESET 	102  	/* Connection aborted by network. 	*/
#define ENETUNREACH 	101  	/* Network unreachable.			*/
#define ENFILE 		23  	/* Too many files open in system. 	*/
#define ENOBUFS 	105  	/* No buffer space available.		*/
#define ENODATA 	61  	/* No msg is avail on  STREAM head .... */
#define ENODEV 		19  	/* No such device.			*/
#define ENOENT 		2  	/* No such file or directory.		*/
#define ENOEXEC 	8  	/* Executable file format error. 	*/
#define ENOLCK 		37  	/* No locks available.			*/
#define ENOLINK 	67  	/* Reserved.				*/
#define ENOMEM 		12  	/* Not enough space.			*/
#define ENOMSG 		42  	/* No message of the desired type. 	*/
#define ENOPROTOOPT 	92  	/* Protocol not available.		*/
#define ENOSPC 		28  	/* No space left on device.		*/
#define ENOSR 		63  	/* No STREAM resources.			*/
#define ENOSTR 		60  	/* Not a STREAM.			*/
#define ENOSYS 		38  	/* Function not supported.		*/
#define ENOTCONN 	107  	/* The socket is not connected.		*/
#define ENOTDIR 	20  	/* Not a directory.			*/
#define ENOTEMPTY 	39  	/* Directory not empty.			*/
#define ENOTSOCK 	88  	/* Not a socket.			*/
/* #define ENOTSUP  */  	/* Not supported.			*/
#define ENOTTY 		25  	/* Inappropriate I/O control operation. */
#define ENXIO 		6  	/* No such device or address.		*/
#define EOPNOTSUPP 	95  	/* Operation not supported on socket. 	*/
#define EOVERFLOW 	75  	/* Val too large to be stored in data type. */
#define EPERM 		1  	/* Operation not permitted.		*/
#define EPIPE 		32  	/* Broken pipe.				*/
#define EPROTO 		71  	/* Protocol error.			*/
#define EPROTONOSUPPORT 93  	/* Protocol not supported.		*/
#define EPROTOTYPE 	91  	/* Protocol wrong type for socket. 	*/
#define ERANGE 		34  	/* Result too large.			*/
#define EROFS 		30  	/* Read-only file system.		*/
#define ESPIPE 		29  	/* Invalid seek.			*/
#define ESRCH 		3  	/* No such process.			*/
#define ESTALE 		116  	/* Reserved.				*/
#define ETIME 		62  	/* Stream ioctl() timeout.		*/
#define ETIMEDOUT 	110  	/* Connection timed out.		*/
#define ETXTBSY 	26  	/* Text file busy.			*/
#define EWOULDBLOCK EAGAIN 	/* Operation would block (EAGAIN) ..... */
#define EXDEV 		18  	/* Cross-device link.			*/
