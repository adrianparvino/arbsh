#include <arbprec/arbprec.h>

ARBT arb_place(fxdpnt *a, fxdpnt *b, size_t *cnt, size_t r)
{
	ARBT temp = 0;
	if ((a->rp) < (b->rp))
		if((b->rp) - (a->rp) > r)
			return 0;
	if (*cnt < a->len){
		temp = a->number[a->len - *cnt - 1];
		(*cnt)++;
		return temp;
	}
	(*cnt)++;
	return 0;
}

fxdpnt *arb_add_inter(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	size_t i = 0, j = 0, r = 0;
	int sum = 0, carry = 0;
	size_t width = MAX(a->len, b->len);
	size_t alp = a->lp; // these are cached in case of a = function(a, a, a);
        size_t blp = b->lp; // where the original values would be overwritten
        fxdpnt *c2 = arb_expand(NULL, width * 2);
        c2->lp = MAX(a->lp, b->lp);
        c2->len = 0;
        c2->rp = c2->len - c2->lp;

	for (; i < a->len || j < b->len;c2->len++, ++r){
		sum = arb_place(a, b, &i, r) + arb_place(b, a, &j, r) + carry;
		carry = 0;
		if(sum >= base){
			carry = 1;
			sum -= base;
		}
		c2->number[c2->len] = sum;
	}
	if (carry){
		c2->number[c2->len++] = 1;
		c2->lp += 1;
	}
	
	c = arb_expand(c, width * 2);
	arb_copyreverse(c, c2);
	arb_free(c2);
	c->lp = MAX(alp, blp);
	c->rp = c->len - c->lp;
	c = remove_leading_zeros(c);
	return c;
}


fxdpnt *arb_sub_inter(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	size_t width = 0, i = 0, j = 0, r = 0;
	int sum = 0, borrow = 0;
	int mborrow = -1; // mirror borrow must be -1
	int mir = 0;
	size_t z = 0, y = 0; // dummy variables for the mirror
	char *array;
	size_t alp = a->lp; // these are cached in case of a = function(a, a, a);
        size_t blp = b->lp; // where the original values would be overwritten

	width = MAX(a->len, b->len);
	fxdpnt *c2 = arb_expand(NULL, width * 2);
	c2->lp = MAX(a->lp, b->lp);
	c2->len = 0;
	c2->rp = c2->len - c2->lp;
	
	array = arb_malloc((width * 2) * sizeof(ARBT)); // fixme: this is way oversized

	for (; i < a->len || j < b->len;c2->len++, ++r){
		mir = arb_place(a, b, &y, r) - arb_place(b, a, &z, r) + mborrow; // mirror
		sum = arb_place(a, b, &i, r) - arb_place(b, a, &j, r) + borrow;

		borrow = 0;
		if(sum < 0){
			borrow = -1;
			sum += base;
		}
		c2->number[c2->len] = sum;
		// maintain a mirror for subtractions that cross the zero threshold
		y = i;
		z = j;
		mborrow = 0;
		if(mir < 0){
			mborrow = -1;
			mir += base;
		}
		array[c2->len] = (base-1) - mir;
	}
	// a left over borrow indicates that the zero threshold was crossed
	if (borrow == -1){
		ARBT *tmp = c2->number;
		c2->number = array;
		free(tmp);
		arb_flipsign(c2);
	}else 
		free(array);
	c = arb_expand(c, width * 2);
	arb_copyreverse(c, c2);
	arb_free(c2);
	c->lp = MAX(alp, blp);
	c->rp = c->len - c->lp;
	c = remove_leading_zeros(c);
	return c;
}

fxdpnt *arb_add(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	arb_init(c);
	if (a->sign == '-' && b->sign == '-')
		arb_flipsign(c);
	else if (a->sign == '-')
		return c = arb_sub_inter(b, a, c, base);
	else if (b->sign == '-')
		return c = arb_sub_inter(a, b, c, base);
	return c = arb_add_inter(a, b, c, base);
}

fxdpnt *arb_sub(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	arb_init(c);
	if (a->sign == '-' && b->sign == '-')
		arb_flipsign(c);
	else if (a->sign == '-'){
		arb_flipsign(c);
		return c = arb_add_inter(a, b, c, base);
	}
	else if (b->sign == '-' || a->sign == '-')
		return c = arb_add_inter(a, b, c, base);
	return c = arb_sub_inter(a, b, c, base);
}
