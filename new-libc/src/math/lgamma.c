#include "math.h"

double mylgamma(double x)
{
	return (mylog(myfabs(mygamma(x)))); 
}
