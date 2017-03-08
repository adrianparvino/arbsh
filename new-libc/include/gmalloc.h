#include <sys/types.h>
#include <inttypes.h>
#include <sys/syscall.h>
#include <unistd.h>
#define NALLOC 10000


void gfree(void *);
void *gmalloc(size_t);
void *grealloc(void *, size_t);
void *gcalloc(size_t, size_t);


