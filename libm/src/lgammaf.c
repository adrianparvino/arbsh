#include <math.h>

extern int ___signgam;
float ___lgammaf_r(float, int *);

float lgammaf(float x)
{
	return ___lgammaf_r(x, &___signgam);
}
