#ifndef _SYS_SEM_H
#define _SYS_SEM_H
#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_size_t
#include <bits/alltypes.h>

#include <sys/ipc.h>

#define SEM_UNDO	0x1000
#define GETPID		11
#define GETVAL		12
#define GETALL		13
#define GETNCNT		14
#define GETZCNT		15
#define SETVAL		16
#define SETALL		17

struct semid_ds {
	struct ipc_perm sem_perm;
	long sem_otime;
	unsigned long __unused1;
	long sem_ctime;
	unsigned long __unused2;
	unsigned long sem_nsems;
	unsigned long __unused3;
	unsigned long __unused4;
};

#define _SEM_SEMUN_UNDEFINED 1

#define SEM_STAT 18
#define SEM_INFO 19

struct  seminfo {
	int semmap;
	int semmni;
	int semmns;
	int semmnu;
	int semmsl;
	int semopm;
	int semume;
	int semusz;
	int semvmx;
	int semaem;
};

struct sembuf {
	unsigned short sem_num;
	short sem_op;
	short sem_flg;
};

int semctl(int, int, int, ...);
int semget(key_t, int, int);
int semop(int, struct sembuf *, size_t);

#ifdef _GNU_SOURCE
#define __NEED_struct_timespec
#include <bits/alltypes.h>
int semtimedop(int, struct sembuf *, size_t, const struct timespec *);
#endif

#ifdef __cplusplus
}
#endif
#endif
