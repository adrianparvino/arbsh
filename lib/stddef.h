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
#define NULL	0

/* 
	Implementations must potentially support ptrdiff_t, size_t and wchar_t 
	being no larger than type long if determined by confstr().
*/
typedef long ptrdiff_t;

typedef unsigned long size_t;

/* 
	TODO: Add support for __STDC_MB_MIGHT_NEQ_WC__ to wchar_t
	#ifndef __STDC_MB_MIGHT_NEQ_WC__.
*/
typedef long wchar_t;

/* 
	TODO: Add support for offsetof()
	offset in bytes to the structure member ( member-designator ) 
*/
/* offsetof(type, member-designator) */



