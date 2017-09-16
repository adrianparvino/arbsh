#ifndef	_SYS_STATFS_H
#define	_SYS_STATFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/statvfs.h>

typedef struct {
	int __val[2];
} fsid_t;

#include <bits/statfs.h>

int statfs (const char *, struct statfs *);
int fstatfs (int, struct statfs *);

#ifdef _LARGEFILE64_SOURCE
#define statfs64 statfs
#define fstatfs64 fstatfs
#define fsblkcnt64_t fsblkcnt_t
#define fsfilcnt64_t fsfilcnt_t
#endif

#ifdef __cplusplus
}
#endif

#endif
