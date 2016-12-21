/* arctan(x) = x - x^3/3 + x^5/5 - x^7/7 ... */
        /* sin(x) = x - x^3/3! + x^5/5! - x^7/7! ... */
        /* cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! ... */
        /* sin */
        //y += (pow(x,j)/myfactorial(j) * sign);
        /* cos */
        //y += (pow(x,j)/myfactorial(j) * sign) ;


double myatan(double x)
{
        /* pre-computed value based atan -- the maclaurin based 
           atan below it is rather inaccurate */

        double value = x;
        double y=0;

        if(value==0.)
                return 0;
        if(x<0)
                x*=(-1.);

        x=(x-1.)/(x+1.);
        y=x*x;

        x = ((((((((.0028662257 *y - .0161657367)*y + .0429096138)*y -
                    .0752896400)*y + .1065626393)*y - .1420889944)*y +
                    .1999355085)*y - .3333314528)*y + 1)*x;

        x= .785398163397 +x;

        if ( value < 0 )
                return x = x * -1;
        else
                return x;

}


double mycos(double x)
{
        int i, j, toggle = 1;
        double product;
        double last;
        double sum;

        sum = 0.0;
        last = 0;

        while ( x >= (2*PI))
                x -= (2*PI);

        while ( x < 0 )
                x += (2*PI);


        for (i = 0; i < 10000 ; i++)
        {
                product = 1.0;

                for (j = (2*i) ; j > 0 && product > .0000000000000001 ; j--)
                {
                        product *= x / j;

                }
                sum += product * toggle;

                if ( sum == last )
                        break;
                last = sum;

                toggle = -toggle;
        }

        return sum;
}




                //x = 1/2 * PI - atan (x);

                // 2 atan((sqrt(1+x^2)-1)/x)
               // x = PI - myatan(x/ 2);
        //      x = -atan(-x);
        //arctan (1/x) = 1/2 * pi - arctan (x), when x > 0
        //      x = x - (2*PI) * (int)(x/2*PI);



double myatan(double value)
{
        double sign=1.;
        double x=value;
        double y=0;
        if ( value < 0 )
                x = myfabs(value);

        if(value==0.)
                return 0;
        if(x<0)
        {
                sign=(-1.);
                x*=(-1.);
        }
        x=(x-1.)/(x+1.);
        y=x*x;

        x = ((((((((.0028662257*y - .0161657367)*y + .0429096138)*y -
             .0752896400)*y + .1065626393)*y - .1420889944)*y +
             .1999355085)*y - .3333314528)*y + 1)*x;
        x= .785398163397 + sign*x;
        if(x< MINDOUBLE)
                x=0.;
        if ( value < 0 )
                return x = x * -1;
        else
                return x;
}

double myasin(double x)
{
        /* arcsin(x) = arctan(x/sqrt(1-x^2)) */
        return myatan(x / mysqrt( 1 - mypow(x, 2)));
}

double myacos(double x)
{
        /* arccos(x) = pi/2 - arctan(x/sqrt(1-x^2)) */
        return PI/2 - myatan(x/mysqrt(1 - mypow(x, 2)));
}




printf(" ab_ratio (%lf) *= (1.0 + 2.0 * %lf) / (2.0 + 2.0 * %lf) \n",ab_ratio, i, i );		printf(" ab_ratio (%lf) *= (1.0 + 2.0 * %lf) / (2.0 + 2.0 * %lf) \n",ab_ratio, i, i );

    while ( 1 )
        {
                n += 2.0;
                i += 1;
                // (pow(x, 9.000000) / 9.000000) 
                ab_ratio *= (1.0 + 2.0 * i) / (2.0 + 2.0 * i);
                printf(" ab_ratio (%lf) *= (1.0 + 2.0 * %lf) / (2.0 + 2.0 * %lf) \n",ab_ratio, i, i );
                step = ab_ratio * (pow(x, n) / n);
                printf("step (%lf) = ab_ratio (%lf) * (pow(x, %lf) / %lf) \n", step, ab_ratio  , n, n);

                xn = (xn + step);
                if (xn == last)
                        break;
                last = xn;

        }
        return xn;



//double myasin(double x)
//{
//      /* arcsin(x) = arctan(x/sqrt(1-x^2)) */ 
//      return myatan(x / mysqrt( 1 - mypow(x, 2)));
//}

//double myacos(double x)
//{ 
        /* arccos(x) = pi/2 - arctan(x/sqrt(1-x^2)) */
//      return PI/2 - myatan(x/mysqrt(1 - mypow(x, 2)));
//}

double myatan(double value)
{
        double sign=1.;
        double x=value;
        double y=0;
        if ( value < 0 )
                x = myfabs(value);

        if(value==0.)
                return 0;
        if(x<0)
        {
                sign=(-1.);
                x*=(-1.);
        }
        x=(x-1.)/(x+1.);
        y=x*x;

        x = ((((((((.0028662257*y - .0161657367)*y + .0429096138)*y -
             .0752896400)*y + .1065626393)*y - .1420889944)*y +
             .1999355085)*y - .3333314528)*y + 1)*x;
        x= .785398163397 + sign*x;
        if(x< MINDOUBLE)
                x=0.;
        if ( value < 0 )
                return x = x * -1;
        else
                return x;
}

double myasin(double x)
{
        /* arcsin(x) = arctan(x/sqrt(1-x^2)) */
        return myatan(x / mysqrt( 1 - mypow(x, 2)));
}

double myacos(double x)
{
        /* arccos(x) = pi/2 - arctan(x/sqrt(1-x^2)) */
        return PI/2 - myatan(x/mysqrt(1 - mypow(x, 2)));
}


double Mul2ArcTan(double x)
{       
        //return  x - pow(x, 3)/3.0 + pow(x, 5)/5.0 - pow(x, 7)/7 + pow(x,9)/9 - pow(x, 11)/11;// + pow(x, 13)/13 - pow(x, 15)/15 + pow(x, 17)/17 - pow(x, 19)/19;


}



double mycos(double x)
{
        int i, j, toggle = 1;
        double angle, product, sum = 0.0;

        angle = x;

        while (angle >= (2*PI))
                angle -= (2*PI);

        while ( angle < 0 )
                angle += (2*PI);

        for (i = 0; i < 100 ; i++)
        {
                product = 1.0;
        //      for (j = (2*i) ; j > 0 ; j--) 
                for (j = (2*i) ; j > 0 && product >DBL_EPSILON   ; j--)
                {
                        product *= angle / j;
        //              printf(" product *= angle / j  =  %10.10lf *= %10.10lf / %d\n",  product, angle, j);

                }
        //      printf("sum += product * toggle  =   %10.10lf *= %10.10lf * %d \n",sum, product, toggle);
                sum += product * toggle;

                toggle = -toggle;
        }

        return sum;
}
double myatan2(double y, double x) {
        double coeff_1 = PI / 4.;
        double coeff_2 = 3. * coeff_1;
        double abs_y = fabs(y);
        double angle;
        if (x >= 0.) {
                double r = (x - abs_y) / (x + abs_y);
                angle = coeff_1 - coeff_1 * r;
        } else {
                double r = (x + abs_y) / (abs_y - x);
                angle = coeff_2 - coeff_1 * r;
        }
        return y < 0. ? -angle : angle;
}
int arctan2(int y, int x)
{
   int angle, abs_y = y;
   if(abs_y<0) abs_y=0-y;
 
   if(x>=0) angle = (45 - (45 * (x - abs_y) / (x + abs_y)));
   else if(x<0) angle = (135 - (45 * (x + abs_y) / (abs_y - x)));
 
   if (y < 0) return(360-angle);     // negate if in quad III or IV
   else if(y >= 0) return(angle);
}

High precision sine/cosine (~8x faster)

//always wrap input angle to -PI..PI
if (x < -3.14159265)
    x += 6.28318531;
else
if (x >  3.14159265)
    x -= 6.28318531;

//compute sine
if (x < 0)
{
    sin = 1.27323954 * x + .405284735 * x * x;
    
    if (sin < 0)
        sin = .225 * (sin *-sin - sin) + sin;
    else
        sin = .225 * (sin * sin - sin) + sin;
}
else
{
    sin = 1.27323954 * x - 0.405284735 * x * x;
    
    if (sin < 0)
        sin = .225 * (sin *-sin - sin) + sin;
    else
        sin = .225 * (sin * sin - sin) + sin;
}

//compute cosine: sin(x + PI/2) = cos(x)
x += 1.57079632;
if (x >  3.14159265)
    x -= 6.28318531;

if (x < 0)
{
    cos = 1.27323954 * x + 0.405284735 * x * x;
    
    if (cos < 0)
        cos = .225 * (cos *-cos - cos) + cos;
    else
        cos = .225 * (cos * cos - cos) + cos;
}
else
{
    cos = 1.27323954 * x - 0.405284735 * x * x;

    if (cos < 0)
        cos = .225 * (cos *-cos - cos) + cos;
    else
        cos = .225 * (cos * cos - cos) + cos;
}




#define EPS 0.00000000001
#define my_pow powl
#define my_abs fabsl

double my_arcsin(double x)
{

       if (x > 1 )
        {
        return 0;

        }


    double a, an, b, bn;
    a = an = 1.0;
    b = bn = 2.0;

    unsigned long _n = 0;
    double ab_ratio = 0.5;
    double n = 3.0;
    double xn;
    double xs = x;
    double xp = x;

    xn = xs + ab_ratio * (mypow(xp,n) / n);

   // long double step = EPS;
        double step = 2;
        int i = 0;

    while (fabs(step) >= EPS)
    {
        n += 2.0;

        an += 2.0;
        bn += 2.0;
        a = a * an;
        b = b * bn;

        _n += 1;
        ab_ratio *= (1.0 + 2.0 * _n) / (2.0 + 2.0 * _n);

        xs = xn;
        step = ab_ratio * (mypow(xp,n) / n);
        xn = xs + step;
    }
    return xn;
}


double next(double a, double x, int i)
{
    return a*((pow(2*i-1, 2)) / ((2*i)*(2*i+1)*pow(x, 2)));
}
double my_asin(double x)
{
        while (x>= (2*PI))
               x  -= (2*PI);

        while ( x < 0 )
                x += (2*PI);
    double a = 0;
    int i = 0;
    double sum = 0;
    a = x;
    for(i = 1; i < 23500; i++)
    {
        sum += a;
        a = next(a, x, i);
    }
}

float myarcsin(double angle)
{
        while (angle >= (2*PI))
                angle -= (2*PI);

        while ( angle < 0 )
                angle += (2*PI);

        return angle + (pow(angle, 3.0) / 6.0) + (pow(angle, 5.0) * 0.075) + (pow(angle, 7.0) * 0.0446429);
//      return angle + (pow(angle, 3.0) / 6.0) + (pow(angle, 5.0) * 0.075) + (pow(angle, 7.0));
}


float myarcsin(double angle)
{
        while (angle >= (2*PI))
                angle -= (2/PI);

        while ( angle < 0 )
                angle += (2/PI);

        return angle + (pow(angle, 3.0) / 6.0) + (pow(angle, 5.0) * 0.075) + (pow(angle, 7.0) * 0.0446429);
//      return angle + (pow(angle, 3.0) / 6.0) + (pow(angle, 5.0) * 0.075) + (pow(angle, 7.0));
}


int arctan2(int y, int x)
{
   int angle, abs_y = y;
   if(abs_y<0) abs_y=0-y;

   if(x>=0) angle = (45 - (45 * (x - abs_y) / (x + abs_y)));
   else if(x<0) angle = (135 - (45 * (x + abs_y) / (abs_y - x)));

   if (y < 0) return(360-angle);     // negate if in quad III or IV
   else if(y >= 0) return(angle);
}


/*
double mysin(double x)
{
                while (x >= (2*PI))
                x -= (2*PI);

        while ( x < 0 )
                x += (2*PI);

    int n;
    double val=0;
    for (n=0;n<8;n++)
    {
        double p = pow(-1,n);
        double px = pow(x,2*n+1);
        long fac = myfactorial(2*n+1);
        val += p * px / fac;
    }
    return val;
}
*/

double mysin(double x)
{
                while (x >= (2*PI))
                x -= (2*PI);

        while ( x < 0 )
                x += (2*PI);

    int n;
    double val=0;
    for (n=0;n<8;n++)
    {
        double p = pow(-1,n);
        double px = pow(x,2*n+1);
        long fac = myfactorial(2*n+1);
        val += p * px / fac;
    }
    return val;
}

/*
double mycos(double input)
{
    unsigned int i;
    double sum = 1.0;
 
    for (i = 0; i < 10; i++) 
        sum += pow(-1, i) * pow(input, 2*i) / factorial(2*i); 
    return sum;
}
*/

double mycos(double x)
{
        int i, j, toggle = 1;
        double angle, product, sum = 0.0;
 
        angle = x;

        while (angle >= (2*PI))
                angle -= (2*PI);
 
        for (i = 0; i < 10 ; i++)
        {
                product = 1.0;
                for (j = (2*i); j > 0 ; j--)
                        product *= angle / j;
 
                sum += product * toggle;
                toggle = -toggle;
        }
 
        return sum;
}




double _pow(double a, double b) {
    double c = 1;
    for (int i=0; i<b; i++)
        c *= a;
    return c;
}

double _fact(double x) {
    double ret = 1;
    for (int i=1; i<=x; i++)
        ret *= i;
    return ret;
}

double _sin(double x) {
    double y = x;
    double s = -1;
    for (int i=3; i<=10; i+=2) {
    //    y+=s*(_pow(x,i)/_fact(i));
        y+=s*(pow(x,i)/_fact(i));
//      y+=s*(pow(x,i)/log(i));
        s *= -1;
    }
    return y;
}
double _cos(double x) {
    double y = 1;
    double s = -1;
    for (int i=2; fabs(x) > 100 ; i+=2) {
        y+=s*(_pow(x,i)/_fact(i));
        s *= -1;
    }
    return y;
}
double _tan(double x) {
     return (_sin(x)/_cos(x));
}

double cosinus(double x)
{
        double prec = 5;
    double t , s ;
    int p;
    p = 0;
    s = 1.0;
    t = 1.0;
    while(fabs(t/s) > prec)
    {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
    }
    return s;
}

#include <stdio.h>
#include <math.h> 
#include <stdlib.h>


    #define MAX_DELTA_DOUBLE 1.0E-15
#define EULERS_NUMBER 2.718281828459045

double MathAbs_Double (double x) {
    return ((x >= 0) ? x : -x);
}

int MathAbs_Int (int x) {
    return ((x >= 0) ? x : -x);
}

double MathPow_Double_Int(double x, int n) {
    double ret;
    if ((x == 1.0) || (n == 1)) {
        ret = x;
    } else if (n < 0) {
        ret = 1.0 / MathPow_Double_Int(x, -n);
    } else {
        ret = 1.0;
        while (n--) {
            ret *= x;
        }
    }
    return (ret);
}

double MathLn_Double(double x) {
    double ret = 0.0, d;
    if (x > 0) {
        int n = 0;
        do {
            int a = 2 * n + 1;
            d = (1.0 / a) * MathPow_Double_Int((x - 1) / (x + 1), a);
            ret += d;
            n++;
        } while (MathAbs_Double(d) > MAX_DELTA_DOUBLE);
    } else {
        printf("\nerror: x < 0 in ln(x)\n");
        exit(-1);
    }
    return (ret * 2);
}

double MathExp_Double(double x) {
    double ret;
    if (x == 1.0) {
        ret = EULERS_NUMBER;
    } else if (x < 0) {
        ret = 1.0 / MathExp_Double(-x);
    } else {
        int n = 2;
        double d;
        ret = 1.0 + x;
        do {
            d = x;
            for (int i = 2; i <= n; i++) {
                d *= x / i;
            }
            ret += d;
            n++;
        } while (d > MAX_DELTA_DOUBLE);
    }
    return (ret);
}

double MathPow_Double_Double(double x, double a) {
    double ret;
    if ((x == 1.0) || (a == 1.0)) {
        ret = x;
    } else if (a < 0) {
        ret = 1.0 / MathPow_Double_Double(x, -a);
    } else {
     //   ret = MathExp_Double(a * MathLn_Double(x));
	//ret = MathExp_Double(a * log(x));
	ret = exp(a * log(x));
    }
    return (ret);
}
		





int main(int argc, char *argv[])
{
	double ret; 

//	ret = exp(strtod(argv[1], 0));
  //      printf("libc exp    %lf\n", ret); 


//	ret = exp(strtod(argv[1], 0), strtod(argv[2], 0));
  //      printf("my exp      %lf\n", ret);
	ret = MathPow_Double_Double(strtod(argv[1], 0), strtod(argv[2], 0));
        printf("my pow      %lf\n", ret);

	ret = pow(strtod(argv[1], 0), strtod(argv[2], 0));
        printf("libc pow      %lf\n", ret);


	return 0;

}



double pow3(double base, double ex)
{

        double half_pow;
        // power of 0
        if (ex == 0)
        {
                return 1;
        // negative exponent
        }else if( ex < 0){
                return 1 / pow3(base, -ex);
        // even exponent
        }else if ((int)ex % 2 == 0)
        {
                half_pow = pow3(base, ex/2);
                return half_pow * half_pow;
        //integer exponent
        }else{
                return base * pow3(base, ex - 1);
        }
}

