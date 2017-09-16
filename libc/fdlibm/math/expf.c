/* origin: FreeBSD /usr/src/lib/msun/src/e_expf.c */
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

#include "libm.h"

static const float
halF[2] = {0.5,-0.5,},
huge    = 1.0e+30,
o_threshold =  8.8721679688e+01,  /* 0x42b17180 */
u_threshold = -1.0397208405e+02,  /* 0xc2cff1b5 */
ln2HI[2]   = { 6.9314575195e-01,  /* 0x3f317200 */
              -6.9314575195e-01,},/* 0xbf317200 */
ln2LO[2]   = { 1.4286067653e-06,  /* 0x35bfbe8e */
              -1.4286067653e-06,},/* 0xb5bfbe8e */
invln2 = 1.4426950216e+00,        /* 0x3fb8aa3b */
/*
 * Domain [-0.34568, 0.34568], range ~[-4.278e-9, 4.447e-9]:
 * |x*(exp(x)+1)/(exp(x)-1) - p(x)| < 2**-27.74
 */
P1 =  1.6666625440e-1, /*  0xaaaa8f.0p-26 */
P2 = -2.7667332906e-3; /* -0xb55215.0p-32 */

static const volatile float twom100 = 7.8886090522e-31; /* 2**-100=0x0d800000 */

float expf(float x)
{
	float y,hi=0.0,lo=0.0,c,t,twopk;
	int32_t k=0,xsb;
	uint32_t hx;

	GET_FLOAT_WORD(hx, x);
	xsb = (hx>>31)&1;  /* sign bit of x */
	hx &= 0x7fffffff;  /* high word of |x| */

	/* filter out non-finite argument */
	if (hx >= 0x42b17218) {  /* if |x|>=88.721... */
		if (hx > 0x7f800000)  /* NaN */
			return x+x;
		if (hx == 0x7f800000)  /* exp(+-inf)={inf,0} */
			return xsb==0 ? x : 0.0;
		if (x > o_threshold)
			return huge*huge; /* overflow */
		if (x < u_threshold)
			return twom100*twom100; /* underflow */
	}

	/* argument reduction */
	if (hx > 0x3eb17218) {  /* if  |x| > 0.5 ln2 */
		if (hx < 0x3F851592) {  /* and |x| < 1.5 ln2 */
			hi = x-ln2HI[xsb];
			lo = ln2LO[xsb];
			k = 1 - xsb - xsb;
		} else {
			k  = invln2*x + halF[xsb];
			t  = k;
			hi = x - t*ln2HI[0];  /* t*ln2HI is exact here */
			lo = t*ln2LO[0];
		}
		STRICT_ASSIGN(float, x, hi - lo);
	} else if(hx < 0x39000000)  {  /* |x|<2**-14 */
		/* raise inexact */
		if (huge+x > 1.0f)
			return 1.0f + x;
	} else
		k = 0;

	/* x is now in primary range */
	t = x*x;
	if (k >= -125)
		SET_FLOAT_WORD(twopk, 0x3f800000+(k<<23));
	else
		SET_FLOAT_WORD(twopk, 0x3f800000+((k+100)<<23));
	c  = x - t*(P1+t*P2);
	if (k == 0)
		return 1.0f - ((x*c)/(c - 2.0f) - x);
	y = 1.0f - ((lo - (x*c)/(2.0f - c)) - hi);
	if (k < -125)
		return y*twopk*twom100;
	if (k == 128)
		return y*2.0f*0x1p127f;
	return y*twopk;
}
