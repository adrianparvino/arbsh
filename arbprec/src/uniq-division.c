#include <arbprec.h>
/*
	uniq-division is a simple, but slow algorithm which I devised myself in
	the winter of 2016. It's here mostly for reference. Please instead use
	"algd.c" which is also inside of arbsh/arbprec, Algd.c uses a similiar
	long division algorithm but was devised by Knuth and is much faster.
*/

fxdpnt *arb_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	size_t i = 0;
	size_t j = 0;
	size_t z = 0;
	size_t width = a->len + b->len;
	size_t diff = 0;
	size_t off = 0;
	char *mir = arb_malloc(sizeof(ARBT) *( width + scale));
	char *tmir = arb_malloc(sizeof(ARBT) * width);
	int sum = 0;
	int rec = 0;

	c = arb_expand(c, a->len + b->len);
	arb_init(c);
	arb_setsign(a, b, c);
	
	memset(mir + a->len, 0, width - a->len + scale);
	memcpy(mir, a->number, a->len);
	c->number[z] = 0;

	/* count the zeros to the right of the radix before a non-zero value */
	while (b->number[off] == 0 && off < b->len)
		++off;

	if (rl(a) < rl(b))
	{
		diff = rl(b) - rl(a) - 1;
		memset(c->number, 0, diff);
		c->len = z = diff;
		c->lp = 0 + off;
		c->number[z] = 0;
	}
	else {
		c->lp = rl(a) - rl(b) + off + 1;
	}

	for (; z < a->len + diff;)
	{
		for (rec = 0, i = off, j = z - diff ; i < b->len ; j++ ,i++)
		{
			sum = (mir[j]) - (b->number[i]);
			if (sum < 0)
			{
				if (j == z - diff)
				{
					mir[j + 1] += ((mir[j]) * base);
					z++;
					c->len++;
					c->number[z] = 0;
				}
				else
				{
					mir[j - 1] -= 1;
					mir[j] += base;
				}
				rec = 1;
				break;

			}
			tmir[j] = sum;
		}
		if (rec == 0)
		{
			memcpy(mir, tmir, j);
			c->number[z] += 1;
		}
	}
	free(mir);
	free(tmir);
	return c;
}

