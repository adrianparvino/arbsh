#ifndef	_GLOB_H
#define	_GLOB_H

#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_size_t

#include <bits/alltypes.h>

typedef struct {
	size_t gl_pathc;
	char **gl_pathv;
	size_t gl_offs;
	int __dummy1;
	void *__dummy2[5];
} glob_t;

int  glob(const char *, int, int (*)(const char *, int), glob_t *);
void globfree(glob_t *);

#define GLOB_ERR      0x01
#define GLOB_MARK     0x02
#define GLOB_NOSORT   0x04
#define GLOB_DOOFFS   0x08
#define GLOB_NOCHECK  0x10
#define GLOB_APPEND   0x20
#define GLOB_NOESCAPE 0x40
#define	GLOB_PERIOD   0x80

#define GLOB_NOSPACE 1
#define GLOB_ABORTED 2
#define GLOB_NOMATCH 3
#define GLOB_NOSYS   4

#ifdef _LARGEFILE64_SOURCE
#define glob64 glob
#define globfree64 globfree
#endif

#ifdef __cplusplus
}
#endif

#endif
