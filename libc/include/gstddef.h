/*
	
	stddef.h - standard type definitions

	SYNOPSIS #include <stddef.h> 


	2017, Copyright, CM Graff, "stddef.h"
	See grafland/LICENSE for copying details.
*/ 


/* 
	NULL should be a cast to type void * according to POSIX 2008,
	however the C standard leaves it implementation defined.
*/ 
#ifndef NULL
#define NULL ((void *) 0)
#endif

/* 
	Implementations must potentially support ptrdiff_t, size_t and wchar_t 
	being no larger than type long if determined by confstr().
*/

#undef ptrdiff_t
typedef long ptrdiff_t;


#undef size_t
typedef unsigned long size_t;

/* 
	TODO: Add support for __STDC_MB_MIGHT_NEQ_WC__ to wchar_t
	#ifndef __STDC_MB_MIGHT_NEQ_WC__.
*/
//typedef long wchar_t;

/* 
	TODO: Add support for offsetof()
	offset in bytes to the structure member ( member-designator ) 
*/
/* offsetof(type, member-designator) */



/* putting ssize_t here is not part of POSIX */

#undef ssize_t
typedef long ssize_t;

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

/* putting pid_t here is not POSIX */

//typedef size_t pid_t;

