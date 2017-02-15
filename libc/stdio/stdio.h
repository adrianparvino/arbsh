#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../stddef/stddef.h"
#include "../fcntl/fcntl.h"
#include "../string/string.h"

/* defines */
/* ------- */
#define GGNULL		0
#define GEOF		(-1)
#define GBUFSIZ		4096
#define GBUFSIZEE	4096
#define IRCBUFSIZ	4096
#define OPEN_MAX	12
#define PERMS		0666

/* type definitions */
/* ---------------- */
typedef struct _iobuf {
	int cnt;		/* characters left */
	char *ptr;		/* next character position */
	char *base;		/* location of buffer */
	int flag;		/* a bool to see if the structure is valid */
	int fd;			/* a file descriptor */
	int write;		/* not used */
	int read;		/* not used */
	int append;		/* not used */
	int unbuf;		/* output must be unbuffered, for stderr or failed malloc */
}GFILE;
extern GFILE _iob[OPEN_MAX];
#define gstdin  (&_iob[0])
#define gstdout  (&_iob[1])
#define gstderr  (&_iob[2])
GFILE *gstdhold; 


/* Function prototypes */
/* ------------------- */
int ggetc_inter(GFILE *);
int gputc_inter(int, GFILE *);
int ggetchar(void);
int gputchar(char);
int ggetc(GFILE *);
int gputc(int, GFILE *); 
ssize_t ggetline (char **, size_t *, GFILE *);
ssize_t ggetdelim(char **, size_t *, char, GFILE *);
int gprintf_inter(GFILE *, int, char *, size_t, int, char *, va_list);
int gprintf(char *, ...);
int gsprintf(char *, char *, ...);
int gsnprintf(char *, size_t, char *, ...);
int gdprintf(int, char *, ...);
int gfprintf(GFILE *, char *, ...);
int gvprintf(char *, va_list);
int gvsprintf(char *, char *, va_list);
int gvsnprintf(char *, size_t, char *, va_list);
int gvdprintf(int, char *, va_list);
int gvfprintf(GFILE *, char *, va_list);
size_t gfread(void *, size_t, size_t, GFILE *);
size_t gfwrite(const void *, size_t, size_t, GFILE *);
int gfeof(GFILE *);
int gferror(GFILE *);
int gfileno(GFILE *);


char *gdtoa(char *, double);
size_t uintostrbase(char *, size_t, int);
size_t intostrbase_inter(char *, int, int); 
size_t intostrbase(char *, int, int);


