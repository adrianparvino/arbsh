#define F_DUPFD 1
  
//#define F_DUPFD_CLOEXEC 

#define F_GETFD 2
 
#define F_SETFD 5

#define F_GETFL 3

#define F_SETFL 6

#define F_GETLK 4

#define F_SETLK 7

#define F_SETLKW 8

//#define F_GETOWN 

//#define F_SETOWN

//#define FD_CLOEXEC

#define F_RDLCK 1

#define F_UNLCK 0

#define F_WRLCK 2

//#define O_CLOEXEC

#define O_CREAT 0x0100

//#define O_DIRECTORY

#define O_EXCL 0x0200

#define O_NOCTTY 0x0400

//#define O_NOFOLLOW

#define O_TRUNC 0x0800

//#define O_TTY_INIT

#define O_APPEND 0x1000



//#define O_DSYNC 

#define O_NONBLOCK 0x2000

//#define O_RSYNC

//#define O_SYNC

#define O_ACCMODE 0x0003

//#define O_SEARCH

//#define O_EXEC

#define O_RDONLY 0x0000

#define O_RDWR 0x0002

//#define O_SEARCH

#define O_WRONLY 0x0001

#define AT_FDCWD

#define AT_EACCESS

#define AT_SYMLINK_NOFOLLOW

#define AT_SYMLINK_FOLLOW

#define AT_REMOVEDIR

//#define POSIX_FADV_NORMAL

//#define POSIX_FADV_SEQUENTIAL

//#define POSIX_FADV_RANDOM

//#define POSIX_FADV_WILLNEED

//#define POSIX_FADV_DONTNEED

//#define POSIX_FADV_NOREUSE

//int  creat(const char *, mode_t);

int  creat(const char *, unsigned long long);
int  fcntl(int, int, ...);
int  open(const char *, int, ...);
int  openat(int, const char *, int, ...);
