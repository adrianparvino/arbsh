/**
 * karatsuba-mul.c - Karatsuba Multiplication
 *
 * Author: Bao Hexing <HexingB@qq.com>
 * Created:  9 January 2018
 *
 * Copyright © 2018, Bao Hexing. All Rights Reserved.
 */

#include <arbprec/arbprec.h>

/* use x[len], y[len], to calculate z[2 * len], or z[2 * len - 1] */
/*
  x = x1 * 10 ^ m + x0
  y = y1 * 10 ^ m + y0
  x * y = (x1 * 10 ^ m + x0) * (y1 * 10 ^ m + y0)
  = x1 * y1 * 10 ^ 2m + x1 * y0 * 10 ^ m + x0 * y1 * 10 ^ m + x0 * y0
  = x1 * y1 * 10 ^ 2m + [(x1 + x0) * (y1 + y0) - x1 * y1 - x0 * y0] * 10 ^ m + x0 * y0
  = z1 * 10 ^ 2m + (z2 * z3 - z1 - z4) * 10 ^ m + z4
  let:
  z1 = x1 * y1
  z2 = x1 + x0
  z3 = y1 + y0
  z4 = x0 * y0
  z5 = z2 * z3
*/
static fxdpnt *arb_karatsuba_mul_core(fxdpnt *x, fxdpnt *y, fxdpnt *z, int base)
{
	if (x->len == 0 || y->len == 0) {
		z = arb_expand(z, 1);
		z->lp = z->len = 0;
		return z;
	}

  if (y->len == 1) {
    // arb_expand(z, x->len + 1);
    z = arb_mul(x, y, z, base, 0);
    // z->lp = z->len = x->len + 1;
	// z = remove_leading_zeros(z);
    return z;
  } else if (x->len == 1) {
    // arb_expand(z, y->len + 1);
    z = arb_mul(y, x, z, base, 0);
    // z->lp = z->len = y->len + 1;
	// z = remove_leading_zeros(z);
    return z;
  }

  size_t m = MIN(x->len, y->len) / 2;

  fxdpnt *x1 = arb_expand(NULL, x->len - m); // x1 = arb_expand(x1, x->len - m);
  fxdpnt *y1 = arb_expand(NULL, y->len - m); // y1 = arb_expand(y1, y->len - m);
  fxdpnt *x0 = arb_expand(NULL, m); // x0 = arb_expand(x0, m);
  fxdpnt *y0 = arb_expand(NULL, m); // y0 = arb_expand(y0, m);

  memcpy(x1->number, x->number, (x->len - m) * sizeof (ARBT));
  memcpy(y1->number, y->number, (y->len - m) * sizeof (ARBT));
  memcpy(x0->number, x->number + x->len - m, m * sizeof (ARBT));
  memcpy(y0->number, y->number + y->len - m, m * sizeof (ARBT));

  x1->lp = x1->len = x->len - m;
  y1->lp = y1->len = y->len - m;
  x0->lp = x0->len = m;
  y0->lp = y0->len = m;

  fxdpnt *z1 = arb_karatsuba_mul_core(x1, y1, NULL, base);
  fxdpnt *z2 = arb_add(x1, x0, NULL, base);
  fxdpnt *z3 = arb_add(y1, y0, NULL, base);
  fxdpnt *z4 = arb_karatsuba_mul_core(x0, y0, NULL, base);
  fxdpnt *z5 = arb_karatsuba_mul_core(z2, z3, NULL, base);

  fxdpnt *z6 = arb_sub(z5, z1, NULL, base);
  fxdpnt *z7 = arb_sub(z6, z4, NULL, base);
  z7 = arb_expand(z7, z7->len + m);
  z7->lp += m;
  z7->len += m;

  z1 = arb_expand(z1, z1->len + 2 * m);
  z1->lp += 2 * m;
  z1->len += 2 * m;

  fxdpnt *z8 = arb_add(z1, z7, NULL, base);
  z = arb_add(z8, z4, z, base);

  arb_free(x0);
  arb_free(y0);
  arb_free(x1);
  arb_free(y1);
  arb_free(z1);
  arb_free(z2);
  arb_free(z3);
  arb_free(z4);
  arb_free(z5);
  arb_free(z6);
  arb_free(z7);
  arb_free(z8);

  return z;
}

fxdpnt *arb_karatsuba_mul(fxdpnt *x, fxdpnt *y, fxdpnt *z, int base)
{
  size_t x_lp = x->lp;
  size_t y_lp = y->lp;
  x->lp = x->len;
  y->lp = y->len;
  z = arb_karatsuba_mul_core(x, y, z, base);
  arb_setsign(x, y, z);
  z->len = x->len + y->len;
  z->lp = z->len - (x->len - x_lp) - (y->len - y_lp);
  z = remove_leading_zeros(z);
  return z;
}

