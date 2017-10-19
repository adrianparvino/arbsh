//   The sine is just cosine shifted a half -

// we'll adjust the argument and call the cosine approximation.
//
#include <math.h>
float sin_32(float x);
float cos_32(float x);
float cos_32s(float x);
float cos_52s(float x);
double cos_73s(double x);
double cos_121s(double x);
double driver(double x);
// Math constants 
double const pi=3.1415926535897932384626433;// pi
//double const twopi=2.0*pi;
double const twopi= 6.283185307179586476925286600;
// pi times 2
//double const halfpi=pi/2.0;
double const halfpi= 1.5707963267948966192313216500;


float sin_32(float x){
	return driver(halfpi - x);
}
// pi divided by 2
//
//  This is the main cosine approximation "driver"
// It reduces the input argument's range to [0, pi/2],
// and then calls the approximator. 
//
//float cos_32(float x)
double driver(double x)
{
	int quad;

	x=fmod(x, twopi);

	if(x<0)x= - x;
// cos( - x) = cos(x)
	quad=(int)(x/halfpi);
	// Get quadrant # (0 to 3)
	switch (quad){
		case 0: return  cos_121s(x);
		case 1: return - cos_121s(pi - x);
		case 2: return - cos_121s(x - pi);
		case 3: return  cos_121s(twopi - x);
	}
}

// cos_32s computes cosine (x)
//
//  Accurate to about 3.2 decimal digits over the range [0, pi/2].
//  The input argument is in radians.
//
//  Algorithm:
// cos(x)= c1 + c2*x**2 + c3*x**4
//   which is the same as:
// cos(x)= c1 + x**2(c2 + c3*x**2)
//
float cos_32s(float x)
{
	const float c1= 0.99940307;
	const float c2= - 0.49558072;
	const float c3= 0.03679168;
	float x2;
	// The input argument squared
	x2=x * x;
	return (c1 + x2*(c2 + c3 * x2));
}

// cos_52s computes cosine (x)
//
//  Accurate to about 5.2 decimal digits over the range [0, pi/2].
//  The input argument is in radians.
//
//  Algorithm:
// cos(x)= c1 + c2*x**2 + c3*x**4 + c4*x**6
//   which is the same as:
// cos(x)= c1 + x**2(c2 + c3*x**2 + c4*x**4)
// cos( x)= c1 + x**2(c2 + x**2(c3 + c4*x**2))
//
float cos_52s(float x)
{
	const float c1= 0.9999932946;
	const float c2= - 0.4999124376;
	const float c3= 0.0414877472;
	const float c4= - 0.0012712095;
	float x2;
	// The input argument squared
	x2=x * x;
	return (c1 + x2*(c2 + x2*(c3 + c4*x2)));
}


// cos_73s computes cosine (x)
//
//  Accurate to about 7.3 decimal digits over the range [0, pi/2].
//  The input argument is in radians.
//
//  Algorithm:
// cos(x)= c1 + c2*x**2 + c3*x**4 + c4*x**6 + c5*x**8
//   which is the same as:
// cos(x)= c1 + x**2(c2 + c3*x**2 + c4*x**4 + c5*x**6)
// cos(x)= c1 + x**2(c2 + x**2(c3 + c4*x**2 + c5*x**4))
// cos(x)= c1 + x**2(c2 + x**2(c3 + x**2(c4 + c5*x**2)))
//
double cos_73s(double x)
{
	const double c1= 0.999999953464;
	const double c2= - 0.4999999053455;
	const double c3= 0.0416635846769;
	const double c4= - 0.0013853704264;
	const double c5= 0.00002315393167;
	double x2;
	// The input argument squared
	x2=x * x;
	return (c1 + x2*(c2 + x2*(c3 + x2*(c4 + c5*x2))));
}
// cos_121s computes cosine (x)
//
//  Accurate to about 12.1 decimal digits over the range [0, pi/2].
//  The input argument is in radians.
//
//  Algorithm:
// cos(x)= c1+c2*x**2+c3*x**4+c4*x**6+c5*x**8+c6*x**10+c7*x**12
//   which is the same as:
// cos(x)= c1+x**2 (c2+c3*x**2+c4*x**4+c5*x**6+c6*x**8+c7*x**10)
// cos(x)= c1+x**2(c2+x**2(c3+c4*x**2+c5*x**4+c6*x**6+c7*x**8 ))
// cos(x)= c1+x**2(c2+x**2(c3+x**2(c4+c5*x**2+c6*x**4+c7*x**6 )))
// cos(x)= c1+x**2(c2+x**2(c3+x**2(c4+x**2(c5+c6*x**2+c7*x**4 ))))
// cos(x)= c 1+x**2(c2+x**2(c3+x**2(c4+x**2(c5+x**2(c6+c7*x**2 )))))
//
double cos_121s(double x)
{
	const double c1= 0.99999999999925182;
	const double c2= - 0.49999999997024012;
	const double c3= 0.041666666473384543;
	const double c4= - 0.001388888418000423;
	const double c5 = 0.0000248010406484558;
	const double c6= - 0.0000002752469638432;
	const double c7= 0.0000000019907856854;
	double x2;
	// The input argument squared
	x2=x * x;
	return (c1 + x2*(c2 + x2*(c3 + x2*(c4 + x2*(c5 + x2*(c6 + c7*x2))))));
}


int main(void)
{
	printf("%19.19lf\n", driver(123));
	return 0;
}
