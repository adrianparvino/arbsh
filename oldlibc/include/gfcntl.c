
#define F_DUPFD 1
    /* Duplicate file descriptor. */
#define F_GETFD 2
    /* Get file descriptor flags. */
#define F_SETFD 5
    /* Set file descriptor flags.*/
#define F_GETFL 3
    /* Get file status flags and file access modes.*/
#define F_SETFL 6
    /* Set file status flags.*/
#define F_GETLK 4
    /* Get record locking information.*/
#define F_SETLK 7
    /* Set record locking information. */
#define F_SETLKW 8
    /* Set record locking information; wait if blocked. */
//#define F_GETOWN 
    /* Get process or process group ID to receive SIGURG signals. */
//#define F_SETOWN
    /* Set process or process group ID to receive SIGURG signals. */
//#define FD_CLOEXEC
    /* Close the file descriptor upon execution of an exec family function. */ 
#define F_RDLCK 1
    /* Shared or read lock. */
#define F_UNLCK 0
    /* Unlock. */
#define F_WRLCK 2
    /* Exclusive or write lock. */ 
#define O_CREAT 0x0100
    /* Create file if it does not exist. */
#define O_EXCL 0x0200
    /* Exclusive use flag. */
#define O_NOCTTY 0x0400
    /* Do not assign controlling terminal. */
#define O_TRUNC 0x0800
    /* Truncate flag. */
#define O_APPEND 0x1000
    /* Set append mode. */
//#define O_DSYNC 
    /* [SIO] [Option Start] Write according to synchronized I/O data integrity completion. [Option End] */
#define O_NONBLOCK 0x2000
    /* Non-blocking mode. */
//#define O_RSYNC
    /* [SIO] [Option Start] Synchronized read I/O operations. [Option End] */
//#define O_SYNC
    /* Write according to synchronized I/O file integrity completion. */
#define O_ACCMODE 0x0003
    /* Mask for file access modes. */
#define O_RDONLY 0x0000
    /* Open for reading only. */
#define O_RDWR 0x0002
    /* Open for reading and writing. */
#define O_WRONLY 0x0001
    /* Open for writing only. */
//#define POSIX_FADV_NORMAL
    /* The application has no advice to give on its behavior with respect to the specified data. It is the default characteristic if no advice is given for an open file. */
//#define POSIX_FADV_SEQUENTIAL
    /* The application expects to access the specified data sequentially from lower offsets to higher offsets. */
//#define POSIX_FADV_RANDOM
    /* The application expects to access the specified data in a random order. */
//#define POSIX_FADV_WILLNEED
    /* The application expects to access the specified data in the near future. */
//#define POSIX_FADV_DONTNEED
    /* The application expects that it will not access the specified data in the near future. */
//#define POSIX_FADV_NOREUSE
    /* The application expects to access the specified data once and then not reuse it thereafter.  */
