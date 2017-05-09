#include <gstddef.h>
/* definitions */
#define	TOLER	.00001
#define	EULER	2.71828182846
#define	PI	3.14159265359
#define	MYNAN	-1

/* trig */ 
double gsin(double);
double gsinh(double); 
double gasin(double); 

double gtan(double);
double gtanh(double);
double gatan(double); 

double gcos(double);
double newcos(double);
double gcosh(double);
double gacos(double);

/* exp */
double gexp(double);

/* pow */
double gpow(double, double);

/* sqrt */
double gsqrt(double);

/* log */
double glog(double);

/* internal */
double _arg_reduction(double);
int _check_tolerance(double, double);
double aseries_func(double, int);
double series_func(double, int, int, int);

double series_func_driver(double, int);
