#include "stdlib.h"
//#ifdef __NR_brk
void* gsbrk(long x)
{
	void *new;
	void *old;

	old = (void *)syscall(__NR_brk, 0);

	new = (void *)syscall(__NR_brk, ((unsigned long)old) + x);

	if ( (((unsigned long)new) == (((unsigned long)old) + x)) )
		return old;

	return (void *)-1;
}
//#endif

