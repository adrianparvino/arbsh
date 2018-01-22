#include <stdbool.h>

#include <arbprec/arbprec.h>

int _long_sub(ARBT *u, size_t i, ARBT *v, size_t k, int b)
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

int _long_add(ARBT *u, size_t i, ARBT *v, size_t k, int b)
{
	int carry = 0;
	int val = 0;
	for (; k+1 > 0; i--, k--) {
		val = u[i] + v[k] + carry;
		carry = 0;
		if (val >= b) {
			val -= b;
			carry = 1;
		}
		u[i] = val;
	}
	return carry;
}

fxdpnt *arb_alg_d(fxdpnt *num, fxdpnt *den, fxdpnt *q, int b, size_t scale)
{
	ARBT *u;
	ARBT *v;
	ARBT *temp;
	fxdpnt tempnum;
	fxdpnt tempden;
	fxdpnt *pnum;
	fxdpnt *pden;
	ssize_t uscal = 0;
	int out_of_scale = 0;
	size_t quodig = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	size_t j = 0;
	size_t k = 0;
	ARBT qg = 0;
	bool construct = false;

	if (num == q) {
		memcpy(&tempnum, num, sizeof(fxdpnt));
		pnum = &tempnum;
		construct = true;
	}
	else {
		pnum = num;
	}

	if (den == q) {
		memcpy(&tempden, den, sizeof(fxdpnt));
		pden = &tempden;
		construct = true;
	}
	else {
		pden = den;
	}

	if (construct)
		arb_construct(q, maxi(pnum->allocated, pden->allocated, 1));
	else
		arb_init(q);

	assert(q->sign == '+');

	lea = pnum->lp + pden->rp;
	uscal = pnum->rp - pden->rp;
	if (uscal < (ssize_t)scale)
		offset = scale - uscal;
	else
		offset = 0;

	u = arb_calloc(1, (pnum->lp + pnum->rp + offset + 3) * sizeof(ARBT));
	_arb_copy_core(u + 1, pnum->number, (pnum->lp + pnum->rp));

	leb = pden->lp + pden->rp;
	v = pden->number;
	for (;*v == 0;v++,leb--); // this can run leb into the ground, be careful!!

	quodig = scale+1;
	out_of_scale = 0;
	if (leb > lea+scale)
		out_of_scale = 1;
	else
		if (!(leb>lea))
			quodig = lea-leb+scale+1;

	q = arb_expand(q, quodig+scale);
	q->lp = quodig-scale; q->rp = scale; q->len = q->lp + q->rp;

	temp = arb_malloc((leb+1) * sizeof(ARBT));

	if (out_of_scale)
		goto end;

	if (leb >lea)
		k=(leb-lea);

	for ( qg = b-1;j <= lea+scale-leb;++j, ++k, qg = b-1)
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
			if (!(_long_sub(u+leb, j, temp, leb, b)))
				goto D7;
			qg = qg - 1;
			if (_long_add(u+leb, j, v, leb-1, b))
				u[0] = 0;
		}
        D7: // D7.
		q->number[k] = qg;

	}
    end:
	free(temp);
	free(u);

	if (pnum != num)
		arb_destruct(pnum);

	if (pden != den && num != den)
		arb_destruct(pden);

	return q;
}

