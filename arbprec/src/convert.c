#include <arbprec/arbprec.h>
/* log of base table 0 - 50 to simplify access */
double logtable[] = {       0.0000000000000,
 0.0000000000000, 0.3010299956640, 0.4771212547197,
 0.6020599913280, 0.6989700043360, 0.7781512503836,
 0.8450980400143, 0.9030899869919, 0.9542425094393,
 1.0000000000000, 1.0413926851582, 1.0791812460476,
 1.1139433523068, 1.1461280356782, 1.1760912590557,
 1.2041199826559, 1.2304489213783, 1.2552725051033,
 1.2787536009528, 1.3010299956640, 1.3222192947339,
 1.3424226808222, 1.3617278360176, 1.3802112417116,
 1.3979400086720, 1.4149733479708, 1.4313637641590,
 1.4471580313422, 1.4623979978990, 1.4771212547197,
 1.4913616938343, 1.5051499783199, 1.5185139398779,
 1.5314789170423, 1.5440680443503, 1.5563025007673,
 1.5682017240670, 1.5797835966168, 1.5910646070265,
 1.6020599913280, 1.6127838567197, 1.6232492903979,
 1.6334684555796, 1.6434526764862, 1.6532125137753,
 1.6627578316816, 1.6720978579357, 1.6812412373756,
 1.6901960800285};


fxdpnt *convert(fxdpnt *a, fxdpnt *b, int ibase, int obase)
{
	arb_copy(b, a);
	ARBT *p;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	int lever = 1;
	int carry = 0;
	int prod = 0;
	p = arb_calloc(a->len, sizeof(ARBT));
	ARBT *array = arb_calloc(a->len, sizeof(ARBT));
	memcpy(array, a->number, a->len * sizeof(ARBT));
	for (; i < a->len + k || lever; i++)
	{ 
		lever = 1;
		if (i < k)
			carry = 0;
			
		else
			carry = array[i-k];
	
		prod = 0;
		for (j = a->len + k; j > 0; j--) {
			prod = (p[j-1] * ibase) + carry;
			p[j-1] = prod % obase;
			carry = prod / obase;
		}
		if (carry)
		{
			++k;
			p = realloc(p, (a->len + k) * sizeof(ARBT));
			memset(p, 0, (a->len + k) * sizeof(ARBT));
			b->len++;
			b->lp++;
			i = 0;
		}else {
			lever = 0;
		}
	}
	b->number = p;

	return b;
}

