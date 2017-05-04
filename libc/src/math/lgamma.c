#include "math.h"

double glgamma(double x)
{
	return (glog(gfabs(ggamma(x)))); 
}
