#include <arbprec/arbprec.h>

fxdpnt *new_addition(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	// NOTE: reverse add and sub only have a speed benefit when the length of the number is unknown
	//       in real life arbitrary precision we always know their length
	// We are NOT computing in reverse so:

	// bring down the extra width of the longest number to the left of the radix into the answer
	// start the computation applying the place function to compensate for exhausted zeros
	//       OR
	// this may be simpler to have a second function. it's going to be hard to reuse long_add_core
	// ideally long_add could simply be called twice, perhaps by overflowing the first digit and allowing it to resolve

	// NOTE: long_add will not be interfered with during the initial computation because there is no way to 
	//       overflow during a carry down of radix left mixmatch

	// NOTE: long_sub and add need to be redesigned to have a third "answer" value
	//       they should be formulated to not interfere with alg D
}

int long_sub(ARBT *u, size_t i, ARBT *v, size_t k, int b)
{ 
	int borrow = 0;
	int val = 0;
	for (; k+1 > 0; i--, k--) {
		val = u[i] - v[k] - borrow; 
		borrow = 0;
		if (val < 0) {
			val += b;
			borrow = 1;
		}
		u[i] = val;
	} 
	return borrow;
}

int long_add(ARBT *u, size_t i, ARBT *v, size_t k, int b)
{
	int carry = 0;
	int val = 0;
	for (; k+1 > 0 ;i--, k--) {
		val = u[i] + v[k] + carry;
		carry = 0;
		if (val > b-1) {
			val -= b;
			carry = 1;
		}
		u[i] = val;
	}
	return carry;
}


fxdpnt *arb_alg_d(fxdpnt *num, fxdpnt *den, fxdpnt *c, int b, int scale)
{
	fxdpnt *q;
	ARBT *u;
	ARBT *v;
	ARBT *temp;
	ARBT qg = 0;
	ssize_t uscal = 0;
	int out_of_scale = 0;
	size_t quodig = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	size_t j = 0;
	int b1 = b-1;

	lea = num->lp + den->rp;
	uscal = num->rp - den->rp;

	if (uscal < scale)
		offset = scale - uscal;
	else
		offset = 0;

	u = arb_malloc((num->lp + num->rp + offset + 2) * sizeof(ARBT));
	memset(u, 0, (num->lp + num->rp + offset + 2) * sizeof(ARBT)); // ref 1
	memcpy(u + 1, num->number, (num->lp + num->rp) * sizeof(ARBT));

	leb = den->lp + den->rp;
	v = arb_malloc((leb+1) * sizeof(ARBT)); //replace this with an expansion of den
	memcpy(v, den->number, leb * sizeof(ARBT));
	//den = arb_expand(den
	v[leb] = 0;

	ARBT *freesave = v;
	for (;*v == 0;v++,leb--);

	quodig = scale+1;
	out_of_scale = 0;
	if (leb > lea+scale) 
		out_of_scale = 1; 
	else
		if (!(leb>lea))
			quodig = lea-leb+scale+1;

	q = arb_new_num(quodig-scale,scale);// FIXME replace this with an expansion of "c"
	memset(q->number, 0, quodig * sizeof(ARBT));
	temp = arb_malloc((leb+1) * sizeof(ARBT));

	if (out_of_scale)
		goto end; 
	// replace this with long-multiplication
	//d = b / (v[0] + 1);

	//if (d != 1){ 
		// 
		//arb_mul_core(u, , &qg, 1, temp, b);
		//arb_short_mul(u, lea+uscal+offset+1, d, b); 
		//arb_short_mul(v, leb, d, b); 
	//} 
	
	for (j=0, qg = b1;j <= lea+scale-leb;++j, qg = b1)
	{
		if (v[0] != u[j])
			qg = (u[j]*b + u[j+1]) / v[0];
		
		if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
		{
			qg = qg - 1;
			if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
				qg = qg - 1;
		} 
		// D4. [Multiply and Subtract]
		if (qg != 0){
			arb_mul_core(v, leb, &qg, 1, temp, b);
			if (!(long_sub(u+leb, j, temp, leb, b)))
				goto D7;
			qg = qg - 1;
			if (long_add(u+leb, j, v, leb-1, b))
				u[0] = 0; 
		}
		D7: // D7.
		q->number[j] = qg;
	}
	// D8. would be the step for remainders
	end: 
	arb_free_num(c); 
	free(temp);
	free(u);
	free(freesave);
	return q;
}

