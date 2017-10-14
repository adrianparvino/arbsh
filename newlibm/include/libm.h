/* origin: FreeBSD /usr/src/lib/msun/src/math_private.h */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#ifndef _LIBM_H
#define _LIBM_H

#include <stdint.h>
//#include <float.h> /* this should probably be removed -- CM Graff */

double scalbn(double, int);
double floor(double);

union fshape {
	float value;
	uint32_t bits;
};

union dshape {
	double value;
	uint64_t bits;
};

#define FORCE_EVAL(x) do {                          \
	if (sizeof(x) == sizeof(float)) {           \
		volatile float ____x;                 \
		____x = (x);                          \
	} else if (sizeof(x) == sizeof(double)) {   \
		volatile double ____x;                \
		____x = (x);                          \
	} else {                                    \
		volatile long double ____x;           \
		____x = (x);                          \
	}                                           \
} while(0)

/* Get two 32 bit ints from a double.  */
#define EXTRACT_WORDS(hi,lo,d)                                  \
do {                                                            \
  union dshape ____u;                                             \
  ____u.value = (d);                                              \
  (hi) = ____u.bits >> 32;                                        \
  (lo) = (uint32_t)____u.bits;                                    \
} while (0)

/* Get a 64 bit int from a double.  */
#define EXTRACT_WORD64(i,d)                                     \
do {                                                            \
  union dshape ____u;                                             \
  ____u.value = (d);                                              \
  (i) = ____u.bits;                                               \
} while (0)

/* Get the more significant 32 bit int from a double.  */
#define GET_HIGH_WORD(i,d)                                      \
do {                                                            \
  union dshape ____u;                                             \
  ____u.value = (d);                                              \
  (i) = ____u.bits >> 32;                                         \
} while (0)

/* Get the less significant 32 bit int from a double.  */
#define GET_LOW_WORD(i,d)                                       \
do {                                                            \
  union dshape ____u;                                             \
  ____u.value = (d);                                              \
  (i) = (uint32_t)____u.bits;                                     \
} while (0)

/* Set a double from two 32 bit ints.  */
#define INSERT_WORDS(d,hi,lo)                                   \
do {                                                            \
  union dshape ____u;                                             \
  ____u.bits = ((uint64_t)(hi) << 32) | (uint32_t)(lo);           \
  (d) = ____u.value;                                              \
} while (0)

/* Set a double from a 64 bit int.  */
#define INSERT_WORD64(d,i)                                      \
do {                                                            \
  union dshape ____u;                                             \
  ____u.bits = (i);                                               \
  (d) = ____u.value;                                              \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */
#define SET_HIGH_WORD(d,hi)                                     \
do {                                                            \
  union dshape ____u;                                             \
  ____u.value = (d);                                              \
  ____u.bits &= 0xffffffff;                                       \
  ____u.bits |= (uint64_t)(hi) << 32;                             \
  (d) = ____u.value;                                              \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */
#define SET_LOW_WORD(d,lo)                                      \
do {                                                            \
  union dshape ____u;                                             \
  ____u.value = (d);                                              \
  ____u.bits &= 0xffffffff00000000ull;                            \
  ____u.bits |= (uint32_t)(lo);                                   \
  (d) = ____u.value;                                              \
} while (0)

/* Get a 32 bit int from a float.  */
#define GET_FLOAT_WORD(i,d)                                     \
do {                                                            \
  union fshape ____u;                                             \
  ____u.value = (d);                                              \
  (i) = ____u.bits;                                               \
} while (0)

/* Set a float from a 32 bit int.  */
#define SET_FLOAT_WORD(d,i)                                     \
do {                                                            \
  union fshape ____u;                                             \
  ____u.bits = (i);                                               \
  (d) = ____u.value;                                              \
} while (0)

/* fdlibm kernel functions */

int    ____rem_pio2_large(double*,double*,int,int,int);
int    ____rem_pio2(double,double*);
double ____sin(double,double,int);
double ____cos(double,double);
double ____tan(double,double,int);
long double ____sinl(long double, long double, int);
long double ____cosl(long double, long double);


// FIXME: not needed when -fexcess-precision=standard is supported (>=gcc4.5)
/*
 * Attempt to get strict C99 semantics for assignment with non-C99 compilers.
 */
#if 1
#define STRICT_ASSIGN(type, lval, rval) do {    \
        volatile type ____v = (rval);             \
        (lval) = ____v;                           \
} while (0)
#else
#define STRICT_ASSIGN(type, lval, rval) ((lval) = (type)(rval))
#endif 

#endif
