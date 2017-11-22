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
	//int uscal = 0;
	ssize_t uscal = 0;//FIXME: figure out how to use a size_t for this
	int out_of_scale = 0; // a bool
	int d = 0; // TODO: research the maximum value of the normalization relative to the base "b"
	size_t quodig = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	size_t j = 0;
	

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
	v = arb_malloc((leb+1) * sizeof(ARBT));
	memcpy(v, den->number, leb * sizeof(ARBT));
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
	//	arb_short_mul(u, lea+uscal+offset+1, d, b); 
	//	arb_short_mul(v, leb, d, b); 
	//} 
	j = 0;
	while (j <= lea+scale-leb)
	{ 
		if (v[0] == u[j])
			qg = b - 1; 
		else	qg = (u[j]*b + u[j+1]) / v[0];
		
		if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
		{
			qg = qg - 1;
			if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
				qg = qg - 1;
		} 
		// D4. [Multiply and Subtract]
		if (qg != 0){
			arb_mul_core(v, leb, &qg, 1, temp, b);
			if (!(long_sub(u, j+leb, temp, leb, b)))
				goto D7;
			qg = qg - 1;
			if (long_add(u, j+leb, v, leb-1, b)) // NOTE: use an offset to u so that long add-sub is not dependent
				u[0] = 0; 
		}
		D7: // D7.
		q->number[j] = qg;
		j++;
	}
	// D8. [Unnormalize]
	// (Q0Q1...Qm)b is the desired quotient, `but` the remainder is ((U(m+1)...U(m+n))b / d)
	// TODO: write a "short division" function to accomplish this and figure and devise a
	// method to make this function do either job. this will probably require another function
	// argument
	end: 
	arb_free_num(c); 
	free(temp);
	free(u);
	free(freesave);
	return q;
}

