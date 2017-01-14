#include <fcntl.h>

/* defines */
/* ------- */
#define GNULL		0
#define GEOF		(-1)
#define GGBUFSIZE	1024
#define OPEN_MAX	20 

/* typedefs */
/*--------- */
typedef struct _giobuf {
	int  cnt;
	char *ptr;
	char *base;
	int  flag;
	int  fd;
}GFILE;

GFILE _giob[OPEN_MAX];

/* enums */
/* ----- */
enum _flags {
	_READ		= 01,
	_WRITE		= 02,
	_UNBUF		= 04,
	_GEOF		= 010,
	_ERR		= 020
};

int _ggfillbug(GFILE *);
GFILE *gfopen(char *, char *);


GFILE _giob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};
#define gstdin		(&_giob[0])
#define gstdout		(&_giob[1])
#define gstderr		(&_giob[2])
#define PERMS		0666
//#define gfeof(p)     ((p)->flag & _GEOF) != 0)
//#define gferror(p)   ((p)->flag & _ERR) != 0)
//#define gfileno(p)   ((p)->fd)
#define gggetc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _ggfillbug(p))
//#define ggputc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p)) 
#define gggetchar()   gggetc(gstdin)
//#define ggputchar(x)  ggputc((x), gstdout)
/* function declarations */
/* --------------------- */

/* functions */
/* --------- */
GFILE *gfopen(char *name, char *mode)
{
	int fd;
	GFILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return GNULL;
	for (fp = _giob; fp < _giob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _giob + OPEN_MAX)
		return GNULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return GNULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = GNULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
} 

int _ggfillbug(GFILE *fp)
{
	int bufsize;

	if ((fp->flag&(_READ|_GEOF|_ERR)) != _READ)
		return GEOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : GGBUFSIZE;
	if (fp->base == GNULL)
		if ((fp->base = (char *) malloc(bufsize)) == GNULL)
			return GEOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _GEOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return GEOF;
	}
	return (unsigned char) *fp->ptr++;
}


