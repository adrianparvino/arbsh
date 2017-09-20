#include <math.h>

// FIXME: use lanczos approximation

float ___lgammaf_r(float, int *);

float tgammaf(float x)
{
	int sign;
	float y;

	y = exp(___lgammaf_r(x, &sign));
	if (sign < 0)
		y = -y;
	return y;
}
