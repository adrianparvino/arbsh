/* origin: FreeBSD /usr/src/lib/msun/src/s_floorf.c */
/*
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */
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
/*
 * floorf(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *      Bit twiddling.
 * Exception:
 *      Inexact flag raised if x not equal to floorf(x).
 */

#include "libm.h"

static const float huge = 1.0e30;

float floorf(float x)
{
	int32_t i0,j0;
	uint32_t i;

	GET_FLOAT_WORD(i0, x);
	// FIXME: signed shift
	j0 = ((i0>>23)&0xff) - 0x7f;
	if (j0 < 23) {
		if (j0 < 0) {  /* |x| < 1 */
			/* raise inexact if x != 0 */
			if (huge+x > 0.0f) {
				if (i0 >= 0)  /* x >= 0 */
					i0 = 0;
				else if ((i0&0x7fffffff) != 0)
					i0 = 0xbf800000;
			}
		} else {
			i = 0x007fffff>>j0;
			if ((i0&i) == 0)
				return x; /* x is integral */
			/* raise inexact flag */
			if (huge+x > 0.0f) {
				if (i0 < 0)
					i0 += 0x00800000>>j0;
				i0 &= ~i;
			}
		}
	} else {
		if (j0 == 0x80)  /* inf or NaN */
			return x+x;
		else
			return x;  /* x is integral */
	}
	SET_FLOAT_WORD(x, i0);
	return x;
}
