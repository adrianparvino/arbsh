#include <sys/mman.h>
#include <sys/syscall.h>
#define NALLOC		8192
#include "../stddef/stddef.h"
#include "../ctype/ctype.h"
#include "../string/string.h"

int gatoi(const char *);
double gatof(const char *);
void *gmalloc(size_t);
void gfree(void *);
void *grealloc(void *, size_t);
void *gsbrk(long);
