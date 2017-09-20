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
#include <float.h>
#include <math.h>
#include <complex.h>

#include "longdbl.h"

//#include "libc.h"

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
		volatile float ___x;                 \
		___x = (x);                          \
	} else if (sizeof(x) == sizeof(double)) {   \
		volatile double ___x;                \
		___x = (x);                          \
	} else {                                    \
		volatile long double ___x;           \
		___x = (x);                          \
	}                                           \
} while(0)

/* Get two 32 bit ints from a double.  */
#define EXTRACT_WORDS(hi,lo,d)                                  \
do {                                                            \
  union dshape ___u;                                             \
  ___u.value = (d);                                              \
  (hi) = ___u.bits >> 32;                                        \
  (lo) = (uint32_t)___u.bits;                                    \
} while (0)

/* Get a 64 bit int from a double.  */
#define EXTRACT_WORD64(i,d)                                     \
do {                                                            \
  union dshape ___u;                                             \
  ___u.value = (d);                                              \
  (i) = ___u.bits;                                               \
} while (0)

/* Get the more significant 32 bit int from a double.  */
#define GET_HIGH_WORD(i,d)                                      \
do {                                                            \
  union dshape ___u;                                             \
  ___u.value = (d);                                              \
  (i) = ___u.bits >> 32;                                         \
} while (0)

/* Get the less significant 32 bit int from a double.  */
#define GET_LOW_WORD(i,d)                                       \
do {                                                            \
  union dshape ___u;                                             \
  ___u.value = (d);                                              \
  (i) = (uint32_t)___u.bits;                                     \
} while (0)

/* Set a double from two 32 bit ints.  */
#define INSERT_WORDS(d,hi,lo)                                   \
do {                                                            \
  union dshape ___u;                                             \
  ___u.bits = ((uint64_t)(hi) << 32) | (uint32_t)(lo);           \
  (d) = ___u.value;                                              \
} while (0)

/* Set a double from a 64 bit int.  */
#define INSERT_WORD64(d,i)                                      \
do {                                                            \
  union dshape ___u;                                             \
  ___u.bits = (i);                                               \
  (d) = ___u.value;                                              \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */
#define SET_HIGH_WORD(d,hi)                                     \
do {                                                            \
  union dshape ___u;                                             \
  ___u.value = (d);                                              \
  ___u.bits &= 0xffffffff;                                       \
  ___u.bits |= (uint64_t)(hi) << 32;                             \
  (d) = ___u.value;                                              \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */
#define SET_LOW_WORD(d,lo)                                      \
do {                                                            \
  union dshape ___u;                                             \
  ___u.value = (d);                                              \
  ___u.bits &= 0xffffffff00000000ull;                            \
  ___u.bits |= (uint32_t)(lo);                                   \
  (d) = ___u.value;                                              \
} while (0)

/* Get a 32 bit int from a float.  */
#define GET_FLOAT_WORD(i,d)                                     \
do {                                                            \
  union fshape ___u;                                             \
  ___u.value = (d);                                              \
  (i) = ___u.bits;                                               \
} while (0)

/* Set a float from a 32 bit int.  */
#define SET_FLOAT_WORD(d,i)                                     \
do {                                                            \
  union fshape ___u;                                             \
  ___u.bits = (i);                                               \
  (d) = ___u.value;                                              \
} while (0)

/* fdlibm kernel functions */

int    ___rem_pio2_large(double*,double*,int,int,int);

int    ___rem_pio2(double,double*);
double ___sin(double,double,int);
double ___cos(double,double);
double ___tan(double,double,int);
double ___expo2(double);
double complex ___ldexp_cexp(double complex,int);

int    ___rem_pio2f(float,double*);
float  ___sindf(double);
float  ___cosdf(double);
float  ___tandf(double,int);
float  ___expo2f(float);
float complex ___ldexp_cexpf(float complex,int);

int ___rem_pio2l(long double, long double *);
long double ___sinl(long double, long double, int);
long double ___cosl(long double, long double);
long double ___tanl(long double, long double, int);

/* polynomial evaluation */
long double ___polevll(long double, const long double *, int);
long double ___p1evll(long double, const long double *, int);

// FIXME: not needed when -fexcess-precision=standard is supported (>=gcc4.5)
/*
 * Attempt to get strict C99 semantics for assignment with non-C99 compilers.
 */
#if 1
#define STRICT_ASSIGN(type, lval, rval) do {    \
        volatile type ___v = (rval);             \
        (lval) = ___v;                           \
} while (0)
#else
#define STRICT_ASSIGN(type, lval, rval) ((lval) = (type)(rval))
#endif


/* complex */

union dcomplex {
	double complex z;
	double a[2];
};
union fcomplex {
	float complex z;
	float a[2];
};
union lcomplex {
	long double complex z;
	long double a[2];
};

/* x + y*I is not supported properly by gcc */
#define cpack(x,y) ((union dcomplex){.a={(x),(y)}}.z)
#define cpackf(x,y) ((union fcomplex){.a={(x),(y)}}.z)
#define cpackl(x,y) ((union lcomplex){.a={(x),(y)}}.z)

#endif
