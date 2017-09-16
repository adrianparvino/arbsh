/* origin: OpenBSD /usr/src/lib/libm/src/ld80/s_asinhl.c */
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
/* asinhl(x)
 * Method :
 *      Based on
 *              asinhl(x) = signl(x) * logl [ |x| + sqrtl(x*x+1) ]
 *      we have
 *      asinhl(x) := x  if  1+x*x=1,
 *                := signl(x)*(logl(x)+ln2)) for large |x|, else
 *                := signl(x)*logl(2|x|+1/(|x|+sqrtl(x*x+1))) if|x|>2, else
 *                := signl(x)*log1pl(|x| + x^2/(1 + sqrtl(1+x^2)))
 */

#include "libm.h"

#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
long double asinhl(long double x)
{
	return asinh(x);
}
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
static const long double
ln2  = 6.931471805599453094287e-01L, /* 0x3FFE, 0xB17217F7, 0xD1CF79AC */
huge = 1.000000000000000000e+4900L;

long double asinhl(long double x)
{
	long double t,w;
	int32_t hx,ix;

	GET_LDOUBLE_EXP(hx, x);
	ix = hx & 0x7fff;
	if (ix == 0x7fff)
		return x + x;   /* x is inf or NaN */
	if (ix < 0x3fde) {      /* |x| < 2**-34 */
		/* return x, raise inexact if x != 0 */
		if (huge+x > 1.0)
			return x;
	}
	if (ix > 0x4020) {      /* |x| > 2**34 */
		w = logl(fabsl(x)) + ln2;
	} else if (ix > 0x4000) { /* 2**34 > |x| > 2.0 */
		t = fabsl(x);
		w = logl(2.0*t + 1.0/(sqrtl(x*x + 1.0) + t));
	} else {                /* 2.0 > |x| > 2**-28 */
		t = x*x;
		w =log1pl(fabsl(x) + t/(1.0 + sqrtl(1.0 + t)));
	}
	if (hx & 0x8000)
		return -w;
	return w;
}
#endif
