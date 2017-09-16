/* origin: FreeBSD /usr/src/lib/msun/src/e_sinh.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* sinh(x)
 * Method :
 * mathematically sinh(x) if defined to be (exp(x)-exp(-x))/2
 *      1. Replace x by |x| (sinh(-x) = -sinh(x)).
 *      2.
 *                                                  E + E/(E+1)
 *          0        <= x <= 22     :  sinh(x) := --------------, E=expm1(x)
 *                                                      2
 *
 *          22       <= x <= lnovft :  sinh(x) := exp(x)/2
 *          lnovft   <= x <= ln2ovft:  sinh(x) := exp(x/2)/2 * exp(x/2)
 *          ln2ovft  <  x           :  sinh(x) := x*shuge (overflow)
 *
 * Special cases:
 *      sinh(x) is |x| if x is +INF, -INF, or NaN.
 *      only sinh(0)=0 is exact for finite x.
 */

#include "libm.h"

static const double huge = 1.0e307;

double sinh(double x)
{
	double t, h;
	int32_t ix, jx;

	/* High word of |x|. */
	GET_HIGH_WORD(jx, x);
	ix = jx & 0x7fffffff;

	/* x is INF or NaN */
	if (ix >= 0x7ff00000)
		return x + x;

	h = 0.5;
	if (jx < 0) h = -h;
	/* |x| in [0,22], return sign(x)*0.5*(E+E/(E+1))) */
	if (ix < 0x40360000) {  /* |x|<22 */
		if (ix < 0x3e300000)  /* |x|<2**-28 */
			/* raise inexact, return x */
			if (huge+x > 1.0)
				return x;
		t = expm1(fabs(x));
		if (ix < 0x3ff00000)
			return h*(2.0*t - t*t/(t+1.0));
		return h*(t + t/(t+1.0));
	}

	/* |x| in [22, log(maxdouble)] return 0.5*exp(|x|) */
	if (ix < 0x40862E42)
		return h*exp(fabs(x));

	/* |x| in [log(maxdouble), overflowthresold] */
	if (ix <= 0x408633CE)
		return h * 2.0 * __expo2(fabs(x)); /* h is for sign only */

	/* |x| > overflowthresold, sinh(x) overflow */
	return x*huge;
}
