#define GNULL       0
#define EOF        (-1)
#define GBUFSIZ     1024
#define OPEN_MAX   20     /* max #files open at once */
typedef struct _iobuf {
    int cnt;          /* characters left */
    char *ptr;        /* next character position */
    char *base;       /* location of buffer */
    int flag;         /* mode of file access */
    int fd;           /* file descriptor */
} GFILE;
extern GFILE _iob[OPEN_MAX];
#define gstdin    (&_iob[0])
#define gstdout   (&_iob[1])
#define gstderr   (&_iob[2])
//enum _flags {
//    _READ   =  01,    /* file open for reading */
//    _WRITE  =  02,    /* file open for writing */
//    _UNBUF  =  04,    /* file is unbuffered */
//    _EOF    =  010,   /* EOF has occurred on this file */
//    _ERR    =  020    /* error occurred on this file */
//};

enum _flags {
    _READ   =  01,    /* file open for reading */
    _WRITE  =  01,
    _UNBUF  =  01,
    _EOF    =  01,
    _ERR    =  01
};

GFILE _iob[OPEN_MAX] = {    /* stdin, stdout, stderr */
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int _fillbuf(GFILE *);
int _flushbuf(int, GFILE *);
#define feof(p)       ((p)->flag & _EOF) != 0)
#define ferror(p)     ((p)->flag & _ERR) != 0)
#define fileno(p)     ((p)->fd)
#define ggetc(p)     (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define gputc(x,p) (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define ggetchar()     ggetc(gstdin)
#define gputchar(x)    gputc((x), gstdout)


#include <fcntl.h>

#define PERMS 0666    /* RW for owner, group, others */
GFILE *gfopen(char *name, char *mode)
{
    int fd;
    GFILE *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
      return GNULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
      if ((fp->flag & (_READ | _WRITE)) == 0)
          break;        /* found free slot */
  if (fp >= _iob + OPEN_MAX)   /* no free slots */
      return GNULL;
  if (*mode == 'w')
      fd = creat(name, PERMS);
  else if (*mode == 'a') {
      if ((fd = open(name, O_WRONLY, 0)) == -1)
          fd = creat(name, PERMS);
      lseek(fd, 0L, 2);
  } else
      fd = open(name, O_RDONLY, 0);
  if (fd == -1)         /* couldn't access name */
      return GNULL;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = GNULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}


/* _fillbuf: allocate and fill input buffer */
int _fillbuf(GFILE *fp)
{
    int bufsize;
    if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
      return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : GBUFSIZ;
  if (fp->base == GNULL)      /* no buffer yet */
      if ((fp->base = (char *) malloc(bufsize)) == GNULL)
           return EOF;       /* can't get buffer */
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
      if (fp->cnt == -1)
           fp->flag |= _EOF;
      else
           fp->flag |= _ERR;
      fp->cnt = 0;
      return EOF;
  }
  return (unsigned char) *fp->ptr++;
}

/* _flushbuf - flush a buffer
 * According to the code on p. 176, _flushbuf
 * is what gputc calls when the buffer is full.
 * EOF as the character causes everything to
 * be written -- I don't tack on the EOF.
 */

int _flushbuf(int c, GFILE *f)
{
    int num_written, bufsize;
    unsigned char uc = c;    

    if ((f->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    if (f->base == GNULL && ((f->flag & _UNBUF) == 0)) {
        /* no buffer yet */
        if ((f->base = malloc(GBUFSIZ)) == GNULL) 
            /* couldn't allocate a buffer, so try unbuffered */
            f->flag |= _UNBUF;
        else {
            f->ptr = f->base;
            f->cnt = GBUFSIZ - 1;
        }
    }
    if (f->flag & _UNBUF) {
        /* unbuffered write */
        f->ptr = f->base = GNULL;
        f->cnt = 0;
        if (c == EOF)
            return EOF;
        num_written = write(f->fd, &uc, 1);
        bufsize = 1;
    } else {
        /* buffered write */
        if (c != EOF)
	{
            //f->ptr = uc;
		f->ptr++;
	}
        bufsize = (int)(f->ptr - f->base);
        num_written = write(f->fd, f->base, bufsize);
        f->ptr = f->base;
        f->cnt = GBUFSIZ - 1;
    }
    if (num_written == bufsize)
        return c;
    else {       
        f->flag |= _ERR;
        return EOF;
    } 
}

/* gfflush */
int gfflush(GFILE *f)
{
    int retval;
    //int i;

    retval = 0;
    if (f == GNULL) {
        /* flush all output streams */ 
	/*
        for (i = 0; i < OPEN_MAX; i++) {
            if ((_iob[i]->flag & _WRITE) && (gfflush(EOF, _iob[i]) == -1))
	
                retval = -1;
        }
	*/
	;
    } else {
        if ((f->flag & _WRITE) == 0)
            return -1;
        _flushbuf(EOF, f);
        if (f->flag & _ERR)
            retval = -1;
    }
    return retval;
}

/* gfclose */
int gfclose(GFILE *f)
{
    int fd;
    
    if (f == GNULL)
        return -1;
    fd = f->fd;
    gfflush(f);
    f->cnt = 0;
    f->ptr = GNULL;
    if (f->base != GNULL)
        free(f->base);
    f->base = GNULL;
    f->flag = 0;
    f->fd = -1;
    return close(fd);
}




