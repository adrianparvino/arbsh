#include <signal.h>
#include <errno.h>
#include "syscall.h"
#include "libc.h"

int sigtimedwait(const sigset_t *mask, siginfo_t *si, const struct timespec *timeout)
{
	int ret;
	do ret = syscall(SYS_rt_sigtimedwait, mask, si, timeout, 8);
	while (ret<0 && errno==EINTR);
	return ret;
}
