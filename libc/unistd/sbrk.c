#include "stddef.h"

#ifdef __NR_brk
void* gsbrk(intptr_t x)
{
	void *new;
	void *old;

	old = (void *)syscall(__NR_brk, 0);

	new = (void *)syscall(__NR_brk, ((uintptr_t)old) + x);

	if ( (((uintptr_t)new) == (((uintptr_t)old) + x)) )
		return old;

	return (void *)-1;
}
#endif

