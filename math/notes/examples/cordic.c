#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* working with IEEE doubles, means there are 53 bits
 * of mantissa
 */
#define MAXBITS         53

/* define this to perform all (non 2power) multiplications
 * and divisions with the cordic linear method.
 */
//#define CORDIC_LINEARx

/* these are the constants needed */
double logCordic(double a);

static double invGain1;
static double invGain2;
static double atanTable[MAXBITS];
static double atanhTable[MAXBITS];

static double gain1Cordic();
static double gain2Cordic();

void initCordic()
{
    /* must call this first to initialise the constants.
     * of course, here i use the maths library, but the
     * values would be precomputed.
     */
    double t = 1;
    int i;
    for (i = 0; i < MAXBITS; ++i) {
        atanTable[i] = atan(t);
        t /= 2;
        atanhTable[i] = 0.5*log((1+t)/(1-t));
    }

    /* set constants */
    invGain1 = 1/gain1Cordic();
    invGain2 = 1/gain2Cordic();
}

void cordit1(double* x0, double* y0, double* z0, double vecmode)
{
    /* this is the circular method. 
     * one slight change from the other methods is the y < vecmode 
     * test. this is to implement arcsin, otherwise it can be
     * y < 0 and you can compute arcsin from arctan using
     * trig identities, so its not essential.
     */

    double t;
    double x, y, z;
    int i;

    t = 1;
    x = *x0; y = *y0; z = *z0;

    for (i = 0; i < MAXBITS; ++i) {
        double x1;

        if (vecmode >= 0 && y < vecmode || vecmode<0  && z >= 0) {
            x1 = x - y*t;
            y = y + x*t;
            z = z - atanTable[i];
        }
        else {
            x1 = x + y*t;
            y = y - x*t;
            z = z + atanTable[i];
        }

        x = x1;
        t /= 2;
    }

    *x0 = x;
    *y0 = y;
    *z0 = z;
}

void cordit2(double* x0, double* y0, double* z0, double vecmode)
{
    /* here's the hyperbolic methods. its very similar to
     * the circular methods, but with some small differences.
     *
     * the `x' iteration have the opposite sign.
     * iterations 4, 7, .. 3k+1 are repeated.
     * iteration 0 is not performed.
     */

    double t;
    double x, y, z;
    int i;

    t = 0.5;
    x = *x0; y = *y0; z = *z0;

    int k = 3;
    for (i = 0; i < MAXBITS; ++i) {
        double x1;
        int j;

        for (j = 0; j < 2; ++j) {
            if (vecmode >= 0 && y < 0 || vecmode<0  && z >= 0) {
                x1 = x + y*t;
                y = y + x*t;
                z = z - atanhTable[i];
            }
            else {
                x1 = x - y*t;
                y = y - x*t;
                z = z + atanhTable[i];
            }
            x = x1;

            if (k) {
                --k;
                break;
            }
            else k = 3;
        }

        t /= 2;
    }

    *x0 = x;
    *y0 = y;
    *z0 = z;
}

void cordit0(double* x0, double* y0, double* z0, double vecmode)
{

    /* the linear methods is the same as the circular but
     * ive simplified out the x iteration as it doesnt change.
     */
    double t;
    double x, y, z;
    int i;

    t = 1;
    x = *x0; y = *y0; z = *z0;

    for (i = 0; i < MAXBITS; ++i) {

        if (vecmode >= 0 && y < 0 || vecmode<0  && z >= 0) {
            y = y + x*t;
            z = z - t;
        }
        else {
            y = y - x*t;
            z = z + t;
        }
        t /= 2;
    }

    *x0 = x;
    *y0 = y;
    *z0 = z;
}

/** Linear features ***********************************************/

double mulCordic(double a, double b)
{
    double x, y, z;
    x = a;
    y = 0;
    z = b;
    cordit0(&x, &y, &z, -1);
    return y;
}

double divCordic(double a, double b)
{
    double x, y, z;
    x = b;
    y = a;
    z = 0;
    cordit0(&x, &y, &z, 0);
    return z;
}

//#ifdef CORDIC_LINEAR
//#define MULT(_a, _b)    mulCordic(_a, _b)
//#define DIVD(_a, _b)    divCordic(_a, _b)
//#else
//#define MULT(_a, _b)    (_a)*(_b)
//#define DIVD(_a, _b)    (_a)/(_b)
//#endif 

/** circular features ***********************************************/

static double gain1Cordic()
{
    /* compute gain by evaluating cos(0) without inv gain */
    double x, y, z;

    x = 1;
    y = 0;
    z = 0;
    cordit1(&x, &y, &z, -1);
    return x;
}

double atanCordic(double a)
{
    /* domain: all a */
    double x = 1;
    double z = 0;
    cordit1(&x, &a, &z, 0);
    return z;
}

double sincosCordic(double a, double* cosp)
{
    /* |a| < 1.74 */
    double sinp = 0;
    *cosp = invGain1;
    cordit1(cosp, &sinp, &a, -1);
    return sinp;
}

double tanCordic(double a)
{
	/* |a| < 1.74 */
	double sinp = 0;
	double cosp = invGain1;
	cordit1(&cosp, &sinp, &a, -1);

	return sinp / cosp;
}

double asinCordic(double a)
{
    /* |a| < 0.98 */
    double x, y, z;
    

    x = invGain1;
    y = 0;
    z = 0;

    int neg = 1;
    if (a < 0) {
        a = -a;
        neg = 0;
    }
        

    cordit1(&x, &y, &z, a);

    if (neg) z = -z;
    return z;
}

/** hyperbolic features ********************************************/

double gain2Cordic()
{
    /* calculate hyperbolic gain */
    double x, y, z;
    x = 1;
    y = 0;
    z = 0;
    cordit2(&x, &y, &z, -1);
    return x;
}

double sinhcoshCordic(double a, double* coshp)
{
	/* |a| < 1.13 */
	double y;
	*coshp = invGain2;
	y = 0;
	cordit2(coshp, &y, &a, -1);
	return y;
}

double tanhCordic(double a)
{
	/* |a| < 1.13 */
	double sinhp, coshp;
	coshp = invGain2;
	sinhp = 0;
	cordit2(&coshp, &sinhp, &a, -1);

	return sinhp / coshp;
}

double atanhCordic(double a)
{
    /* |a| < 1.13 */
    double x, z;
    x = 1;
    z = 0;
    cordit2(&x, &a, &z, 0);
    return z;
}

double logCordic(double a)
{
    /* 0.1 < a < 9.58 */
    double x, y, z;

    x = a + 1;
    y = a - 1;
    z = 0;
    cordit2(&x, &y, &z, 0);
    return 2*z;
}

double sqrtCordic(double a)
{
    /* 0.03 < a < 2 */
    double x, y, z;

    x = a + 0.25;
    y = a - 0.25;
    z = 0;
    cordit2(&x, &y, &z, 0);
    return x * invGain2 ; //MULT(x, invGain2);
}

double expCordic(double a)
{
    double sinhp, coshp;
    coshp = invGain2;
    sinhp = 0;
    cordit2(&coshp, &sinhp, &a, -1);
    return sinhp + coshp;
}

int iiimain(int argc, char *argv[])
{
    /* just run a few tests */ 

	double reta;
        double retb;
	double arg1 = strtod(argv[1], 0);
	double arg2;
	if ( argc > 2 )
        arg2 = strtod(argv[2], 0);


	initCordic();


	reta = atanCordic(arg1);
	printf("atanCordic  %lf\n", reta);

	retb = atan(arg1);
        printf("libc atan      %lf\n", retb); 

	reta = tanCordic(arg1);
        printf("tanCordic         %lf\n", reta);

        retb = tan(arg1);
        printf("libc tan      %lf\n", retb); 

	reta = asinCordic(arg1);
	printf("asinCordic         %lf\n", reta);

        retb = asin(arg1);
        printf("libc asin      %lf\n", retb); 
    
	reta = tanhCordic(arg1);
	printf("tanhCordic  %lf\n", reta);
	
	retb = tanh(arg1);
	printf("libc tanh  %lf\n", retb);

	reta = atanhCordic(arg1);
	printf("atanhCordic  %lf\n", reta); 

	retb = atanh(arg1);
        printf("libc atanh  %lf\n", retb); 

	reta = logCordic(arg1);
	printf("logCordic %lf\n", reta);
	
	retb = log(arg1);
        printf("libc log  %lf\n", retb); 

	reta = sqrtCordic(arg1);
	printf("sqrtCordic %lf\n", reta);

	retb = sqrt(arg1);
        printf("libc sqrt      %lf\n", retb); 

	reta = expCordic(arg1);
	printf("expCordic %lf\n", reta);

	retb = exp(arg1);
	printf("libc exp      %lf\n", retb);


	return 0;
}
