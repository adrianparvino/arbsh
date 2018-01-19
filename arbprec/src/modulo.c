/*
int
bc_modulo (num1, num2, result, scale)
     bc_num num1, num2, *result;
     int scale;
{
  bc_num temp;
  int rscale;

  // Check for correct numbers. 
  if (is_zero (num2)) return -1;

  // Calculate final scale.
  rscale = MAX (num1->n_scale, num2->n_scale+scale);
  init_num (&temp);

  // Calculate it. 
  bc_divide (num1, num2, &temp, scale);
  bc_multiply (temp, num2, &temp, rscale);
  bc_sub (num1, temp, result);
  free_num (&temp);

  return 0;     // Everything is OK. 
}

*/
#include <arbprec/arbprec.h>
fxdpnt *arb_mod(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, size_t scale)
{
	size_t newscale = MAX(a->len, b->len + scale);
	fxdpnt *tmp = arb_expand(NULL, newscale);
	fxdpnt *tmp2 = arb_expand(NULL, newscale);
	tmp = arb_alg_d(a, b, tmp, base, scale);
	tmp2 = arb_mul(tmp, b, tmp2, base, newscale);
	c = arb_sub(a, tmp2, c, base);
	return c;
}
