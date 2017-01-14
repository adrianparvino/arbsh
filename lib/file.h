#include <fcntl.h>

/* defines */
/* ------- */
#define GNULL		0
#define GEOF		(-1)
#define GGBUFSIZE	1024
#define OPEN_MAX	20 
#define gstdin		(&_iob[0])
#define gstdout		(&_iob[1])
#define gstderr		(&_iob[2])
#define PERMS		0666


#define gfeof(p)     ((p)->flag & _EOF) != 0)
#define gferror(p)   ((p)->flag & _ERR) != 0)
#define gfileno(p)   ((p)->fd)
#define gggetc(p)   (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define ggputc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p)) 
#define gggetchar()   gggetc(stdin)
#define ggputcher(x)  ggputc((x), stdout)

/* typedefs */
/*--------- */
typedef struct _iobuf {
	int  cnt;
	char *ptr;
	char *base;
	int  flag;
	int  fd;
} GFILE;

extern GFILE _iob[OPEN_MAX];

/* enums */
/* ----- */
enum _flags {
	_READ		= 01,
	_WRITE		= 02,
	_UNBUF		= 04,
	_GEOF		= 010,
	_ERR		= 020,
	_GEOF_ERR	= 030
};

/* function declarations */
/* --------------------- */
int _fillbuf(GFILE *);
GFILE *gfopen(char *, char *);

/* functions */
/* --------- */
GFILE *gfopen(char *name, char *mode)
{
	int fd;
	GFILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return GNULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
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

int _fillbuf(GFILE *fp)
{
	int bufsize;

	if ((fp->flag&(_READ|_GEOF_ERR)) != _READ)
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

GFILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

