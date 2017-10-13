#ifndef LIBC_H
#define LIBC_H

#include <stdlib.h>
#include <stdio.h>

struct ____libc {
	void *main_thread;
	int threaded;
	int secure;
	size_t *auxv;
	int (*atexit)(void (*)(void));
	void (*fini)(void);
	void (*ldso_fini)(void);
	volatile int threads_minus_1;
	int canceldisable;
	FILE *ofl_head;
	int ofl_lock[2];
};


#if !defined(____PIC____) || 100*____GNUC____+____GNUC_MINOR____ >= 303 || defined(____PCC____) || defined(____TINYC____)

#ifdef ____PIC____
#if ____GNUC____ < 4
#define BROKEN_VISIBILITY 1
#endif
#define ATTR_LIBC_VISIBILITY ____attribute____((visibility("hidden"))) 
#else
#define ATTR_LIBC_VISIBILITY
#endif

extern struct ____libc ____libc ATTR_LIBC_VISIBILITY;
#define libc ____libc

#else

#define USE_LIBC_ACCESSOR
#define ATTR_LIBC_VISIBILITY
extern struct ____libc *____libc_loc(void) ____attribute____((const));
#define libc (*____libc_loc())

#endif


/* Designed to avoid any overhead in non-threaded processes */
void ____lock(volatile int *);
void ____unlock(volatile int *);
int ____lockfile(FILE *);
void ____unlockfile(FILE *);
#define LOCK(x) (libc.threads_minus_1 ? (____lock(x),1) : ((void)(x),1))
#define UNLOCK(x) (libc.threads_minus_1 ? (____unlock(x),1) : ((void)(x),1))

void ____synccall(void (*)(void *), void *);
void ____synccall_wait(void);
int ____setxid(int, int, int, int);

extern char **____environ;
#define environ ____environ

#undef weak_alias
#define weak_alias(old, new) \
	extern ____typeof(old) new ____attribute____((weak, alias(#old)))

#undef LFS64_2
//#define LFS64_2(x, y) weak_alias(x, y)
#define LFS64_2(x, y) extern ____typeof(x) y

#undef LFS64
#define LFS64(x) LFS64_2(x, x##64)

#endif
