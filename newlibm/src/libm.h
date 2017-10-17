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
#include <stdio.h>
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

#define FORCE_EVAL(x){						\
	if (sizeof(x) == sizeof(float)) {			\
		volatile float ____x;				\
		____x = (x);					\
	} else if (sizeof(x) == sizeof(double)) {		\
		volatile double ____x;				\
		____x = (x);					\
	} else {						\
		volatile long double ____x;			\
		____x = (x);					\
	}							\
}

/* Get two 32 bit ints from a double.*/
#define EXTRACT_WORDS(hi,lo,d)					\
{								\
	union dshape ____u;					\
	____u.value = (d);					\
	(hi) = ____u.bits >> 32;				\
	(lo) = (uint32_t)____u.bits;				\
}

/* Get a 64 bit int from a double.*/
#define EXTRACT_WORD64(i,d)					\
{								\
	union dshape ____u;					\
	____u.value = (d);					\
	(i) = ____u.bits;					\
}

/* Get the more significant 32 bit int from a double.*/
#define GET_HIGH_WORD(i,d)					\
{								\
	union dshape ____u;					\
	____u.value = (d);					\
	(i) = ____u.bits >> 32;					\
	printf("GET_HIGH_WORD %d\n", i); \
}

/* Get the less significant 32 bit int from a double.*/
#define GET_LOW_WORD(i,d)					\
{								\
	union dshape ____u;					\
	____u.value = (d);					\
	(i) = (uint32_t)____u.bits;				\
	printf("GET_LOW_WORD %d\n", i); \
}

/* Set a double from two 32 bit ints.*/
#define INSERT_WORDS(d,hi,lo)					\
{								\
	union dshape ____u;					\
	____u.bits = ((uint64_t)(hi) << 32) | (uint32_t)(lo);	\
	(d) = ____u.value;					\
	printf("INSERT_WORDS %lf\n", d); \
}

/* Set a double from a 64 bit int.*/
#define INSERT_WORD64(d,i)					\
{								\
	union dshape ____u;					\
	____u.bits = (i);					\
	(d) = ____u.value;					\
}

/* Set the more significant 32 bits of a double from an int.*/
#define SET_HIGH_WORD(d,hi)					\
{								\
	union dshape ____u;					\
	____u.value = (d);					\
	____u.bits &= 0xffffffff;				\
	____u.bits |= (uint64_t)(hi) << 32;			\
	(d) = ____u.value;					\
	printf("SET_HIGH_WORD %d\n", i); \
}

/* Set the less significant 32 bits of a double from an int.*/
#define SET_LOW_WORD(d,lo)					\
{								\
	union dshape ____u;					\
	____u.value = (d);					\
	____u.bits &= 0xffffffff00000000ull;			\
	____u.bits |= (uint32_t)(lo);				\
	(d) = ____u.value;					\
	printf("SET_LOW_WORD %d\n", i); \
}

/* Get a 32 bit int from a float. */
#define GET_FLOAT_WORD(i,d)					\
{								\
	union fshape ____u;					\
	____u.value = (d);					\
	(i) = ____u.bits;					\
}

/* Set a float from a 32 bit int. */
#define SET_FLOAT_WORD(d,i)					\
{								\
	union fshape ____u;					\
	____u.bits = (i);					\
	(d) = ____u.value;					\
}

/* fdlibm kernel functions */
int ____rem_pio2_large(double *, double *, int, int, int);
int ____rem_pio2(double, double *);
double ____sin(double, double, int);
double ____cos(double, double);
double ____tan(double, double, int);

#define STRICT_ASSIGN(type, lval, rval){			\
	volatile type ____v = (rval);				\
	(lval) = ____v;						\
	printf("STRICT_ASSIGN  lval %19.19lf   rval %19.19lf\n", lval, rval); \
}

//#define STRICT_ASSIGN(type, lval, rval) ((lval) = (type)(rval))
int _check_tolerance(double x, double y);

#endif
