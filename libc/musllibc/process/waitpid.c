#include <sys/wait.h>
#include "syscall.h"
#include "libc.h"

pid_t waitpid(pid_t pid, int *status, int options)
{
	return syscall(SYS_wait4, pid, status, options, 0);
}
