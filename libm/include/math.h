#include <stddef.h>
#include <stdlib.h>
/* definitions */
#define	TOLER	.00001
#define	EULER	2.71828182846
#define PI	3.14159265358979323846264
#define MYNAN	-(0./0.) 

/* trig */ 
double sin(double);
double sinh(double); 
double asin(double); 

double tan(double);
double tanh(double);
double atan(double); 

double cos(double);
//double ewcos(double);
double cosh(double);
double acos(double);

/* exp */
double exp(double);

/* pow */
double pow(double, double);

/* sqrt */
double sqrt(double);

/* log */
double log(double);


double remainder(double, double);
double jn(int, double);
double j0(double);
double j1(double);
double gamma(double);

double fabs(double);

double floor(double);

/* internal */
double _arg_reduction(double);
int _check_tolerance(double, double);
double aseries_func(double, int);
double series_func(double, int, int, int);

double series_func_driver(double, int);

double trigfunc(int, double);

