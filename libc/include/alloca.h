#ifndef	_ALLOCA_H
#define	_ALLOCA_H

#ifdef __cplusplus
extern "C" {
#endif

#define	__NEED_size_t
#include <bits/alltypes.h>

void *alloca(size_t);

#ifdef __GNUC__
#define alloca __builtin_alloca
#endif

#ifdef __cplusplus
}
#endif

#endif
