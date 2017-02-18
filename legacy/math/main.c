#include <stdio.h>  
#include <math.h>   /* for comparative testing */
#include <stdlib.h> /* for strtod */ 
#include <float.h>
#include <stdint.h>
#define PI 3.14159265358979323846264
#define EULER 2.718281828459045
#define EPS 0.00000000001 

#define MYNAN -(0./0.)
double myfabs(double);
unsigned long myfactorial(unsigned long);
double myceil(double);
double myfloor(double);

double mysqrt(double);

double mylog(double);
double myexp(double);
double mypow(double, double);

double mycos(double);
double mysin(double);
double mytan(double);

double myacos(double);
double myasin(double);
double myatan(double);

double myhypot(double, double);
double myremainder(double, double);
double myrint(double);

double myj0(double);
double myj1(double);

double myjn(int, double);

double mygamma(double);


double myacos(double x)
{
        /* identity: acos(x) = (PI / 2) + asin(-x) */
        int i = 0;
        int n = 3;

        double ratio = 0.5;
        double y;
        double z = 0;

        if ( x == 1.0)
                return 0.00000000;
        else if ( x < -1.)
                return MYNAN;
        else if ( x >= 1. )
              return MYNAN;

        y = x;


        while ( 1 )
        {
                y += ratio * (mypow(x, n) / n);
                n += 2;
                i += 1;
                ratio *= (1.0 + 2.0 * i) / (2.0 + 2.0 * i);
                if (y == z)
                        break;
                z = y;
        }


        return (PI / 2) - y;

} 

double myasin(double x)
{
        int i = 0;
        int n = 3;

        double ratio = 0.5;
        double y;
        double z = 0;

        if ( x == 1.)
                return PI/2;
        else if ( x == -1.)
                return -PI/2;
        else if ( x > 1. || x < -1. )
                return MYNAN;

        y = x;

        while ( 1 )
        {
                y += ratio * (mypow(x, n) / n);
                n += 2;
                i += 1;
                ratio *= (1.0 + 2.0 * i) / (2.0 + 2.0 * i);
                if (y == z)
                        break;
                z = y;
        }

        return y;
} 

double myatan(double x)
{
        /* taylor series based atan(x) aproximation */
        int j = 3;
        double z = 0;
        int sign = -1;
        double y = x;

        /* x = x - x^3/3 + x^3/3 - x^3/3 + ...  */
        while (x < 1.0 && x > -1.0 &&  1)
        {
                y += (mypow(x, j)/(j) * sign);
                if (z == y)
                        break;
                z = y;
                j += 2;
                sign = -sign;

        }
        /* x = pi/2 .... if >= 1. */
        if (x >= 1. )
        {
                y = (PI/2);
        }
        /* x = - pi/2 .... if <= -1. */
        else if (x <= -1. )
        {
                y = -(PI/2);
        }
        /* ... 1/x + 1/(3*(x^3)) - 1/(5*x^5) + 1/(7*x^7) - ...  */
        for (j = 1; (x >= 1. || x <= -1.) && 1;)
        {
                y += (1/ (j *(mypow(x, j)))) * sign;
                if (z == y)
                        break;
                z = y;
                j += 2;
                sign = -sign;
        }

        return  y;

} 

double myceil(double x) 
{

	long i = (long)x; 
	if(i < x)
		++i; 
	return (double)i; 
  
} 

double mycos(double x)
{
        int i;
        int j;
        int toggle = 1;
        double product;
        double last;
        double sum;

        sum = 0.0;
        last = 0;

        while ( x >= (2*PI))
                x -= (2*PI);
        while ( x < 0 )
                x += (2*PI);


        for (i = 0; 1 ; i++)
        {
                product = 1.0;

                for (j = (2*i) ; j > 0 ; j--)
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

double myexp(double x)
{
        int i;
        int n = 0;
        double y = 0;
        double d = 0;
        double z = 0;

        if (x == 1.0) {
                y = EULER;
        } else if (x < 0) {
                y = 1.0 / myexp(-x);
        } else {
                n = 2;
                y = 1.0 + x;
                while ( 1 )
                {
                        d = x;
                        for (i = 2; i <= n; i++)
                        {
                                d *= x / i;
                        }
                        y += d;
                        n++;
                        if ( y == z )
                                break;
                        z = y;
                }
        }
        return y;
} 

double myfabs (double x)
{
        return ((x >= 0) ? x : -x);
} 

unsigned long myfactorial(unsigned long x)
{
	if ( x == 0 )
		return 1;
	return (x * myfactorial(x - 1));
	// return n == 0 ? 1 : n * factorial(n - 1);
} 



double myfloor(double x) 
{
	long i = (long)x; 
	if(i > x)
		--i; 
	return (double)i;
}


double mygamma(double x)
{ 
        int a = 12;
        int k;
        double c[a];
        double fac = 1.0;
        double ret;
	

        ret = sqrt(2.0 * PI);

        for( k = 1; k < a ; k++)
        {
                c[k] = ((exp(a - k) * pow(a - k, k - 0.5)) / fac);
                fac *= -k;
        }

        for( k = 1; k < a ; k++)
        {
                ret += (c[k] / (x + k));
        }

        ret *= exp(-(x + a)) * pow(x + a, x + 0.5);
	

        return (ret / x);
}



double myhypot(double x, double y)
{ 
	return mysqrt((x * x) + (y * y));
}


double myj0(double x)
{
	return myjn(0, x);
}


double myj1(double x)
{
	
	return myjn(1, x);
}


double myjn(int y, double x)
{

        int i = 0;
        int n = 20;
        double c = 0.0; 
        double *j;
        double ret = 0; 
	int flip = 0;
	
	/* special cases */
	
	/*   use trigonometric asymptotic aproximation for x >> y */
	if ( x > ( y + 1 ) * 10000)
		return sqrt(2/ (PI * x )) * mycos(x-(2 * y + 1) * (PI/4)); 
	/*   sqrt(2/ (PI * x )) * cos(x-(2 * n + 1) * (PI/4)) */

        if ( x == 0 && y == 0)
                return 1.0;
	else if ( x == 0 )
		return  0.0;
	
	/* reverse negative arguments */
	if ( y < 0 )
	{
		++flip;
		y = -y;
	} 

        if ( x < 0)
	{ 
		++flip; 
                x = -x; 
	}

	/* scale the number of terms */
	n += (x/10); 
	
        if ( x > 5.0 )
                n *= 10;
	

        if (!(j = malloc(sizeof(j) * (y + 5))))
                return MYNAN;

        j[0] = 1.0;
        j[1] = 0.0; 
       


        while ( 1 )
        {
                for (i = y + 4; i > 0; i--)
                {
                        j[i] = j[i-1]; 
                } 

                j[0] = ((2.0 * (n * (j[1] / x))) - j[2]);
                --n;
                if ( n == 0 )
                        break;
                if ( n % 2 )
                        continue;
                c += 2*j[0];
        }



        c += j[0];

        ret = j[y] /= c;
	
	/* If a number was reversed and it was even, reverse it again */
	if ( flip == 1 && y % 2 == 1) 
		ret = -ret;

        free(j);


        return ret;

}



double mylgamma(double x)
{
	return (mylog(myfabs(mygamma(x)))); 
}


double mylog(double x)
{
        int n = 1;
        double y = 0;
        double z = 0;
        /*
                Taylor series 
                ln(x) = 2((x-1/x+1) + 1/3(x-1/x+1)^3 + 1/5(x-1/x+1) + ... ) 
        */

        if (x <= 0 )
                return MYNAN;

        while ( 1 && n < 100000)
        {
                y += (mypow((x - 1)/(x + 1), n) / n );
                n+=2;
                if ( y == z )
                        break;
                z = y;
        }

        return  y * 2;

}


double mypow(double x, double n)
{

        double y = 1;

        /* negative */
        if (n < 0)
                y = 1.0 / mypow(x, -n);
        /* whole number */
        else if (n == (long long)n)
        {
                while (n--)
                      y *= x;
        }
        /* fractional */
        else
                y = myexp(n * mylog(x)); 

        return y;
}




double myremainder(double x, double y)
{ 
	double ret;

	if ( x < 0.0 )
		return x;

	if ( y < 0.0  )
                y = -y;

	ret = x - (y * myfloor(x / y)); 

	return ret; 
}



double mysin(double x)
{
        int i;
        int j;
        int toggle = 1;
        double product;
        double last = 0;
        double sum = 0;

        while ( x >= (2*PI))
                x -= (2*PI);

        while ( x < 0 )
                x += (2*PI);

        for (i = 0; i < 10000 ; i++)
        {
                product = 1.0;
                for (j = (2*i) + 1 ; j > 0 && product > EPS ; j--)
                {
                        product *= (x / j);
                }
                sum += product * toggle;
                toggle = -toggle;
                if ( sum == last )
                        break;
                last = sum;
        }

        return sum;
}




double mysqrt(double x)
{

        /* babylonian method */
        double y; 
        int i;

        if ( x < 0)
                return -MYNAN;

        y = x;

        for(i=0; i < ((x / y) / 2) || i < 10 ; i++)
        {
                y = (( y + x / y ) / 2);
        }

        return y;
}






double mytan(double x)
{ 
        /* x = x + x^3/3 + 2x^5/15 + 17x^7/315 + ...  */
        /* double factorials */
        /* x + 2x^3/3! + 16x^5/5! + 272 x^7/7! */
        /* tan(x) = x + ((1/3) * (x^3)) + ((2/15) * (x^5)) + ((17/315) * (x^7)) + ((62/2835) * (x^9)) + ...     */

        /* tan(x) = x + 2 x^3/3! + 16 x^5/5! + 272 x^7/7! */

	/* not working! fall back to trig identity */
        return (mysin(2*x) / (mycos(2*x) + 1));

}


double mytgamma(double x)
{ 
	return mygamma(x);
}


int main(int argc, char *argv[])
{ 
	double reta = 0;
	double retb = 0; 
	double arg1 = 0;
	double arg2 = 0; 

	if ( argc != 3 )
	{
		printf("please supply 2 numerical arguments\n");
		return 1;
	}

	arg1 = strtod(argv[1], 0);
        arg2 = atoi(argv[2]);


	reta = myj0(arg1);
        printf("myj0         %lf\n", reta); 

	retb = j0(arg1);
        printf("libc j0      %lf\n", retb); 
        printf("\n");

	reta = myj1(arg1);
        printf("myj1         %lf\n", reta); 

	retb = j1(arg1);
        printf("libc j1      %lf\n", retb);
	printf("\n"); 
	
	reta = myjn(arg2, arg1); 
        printf("myjn         %lf\n", reta); 
	retb = jnl(arg2, arg1);
        printf("libc jnl      %lf\n", retb); 
        printf("\n"); 
      
        retb = rint(arg1);
        printf("libc rint      %lf\n", retb);
	printf("\n"); 

	reta = myremainder(arg1, arg2); 
        printf("myremainder         %lf\n", reta);
        retb = remainder(arg1, arg2);
        printf("libc remainder      %lf\n", retb);
        printf("\n"); 

	reta = myhypot(arg1, arg2);
        printf("myhypot         %lf\n", reta);
        retb = hypot(arg1, arg2);
        printf("libc hypot      %lf\n", retb);
        printf("\n");
	
	reta = myceil(arg1);
        printf("myceil         %lf\n", reta);
        retb = ceil(arg1);
        printf("libc ceil      %lf\n", retb);
        printf("\n"); 

	reta = myfloor(arg1);
        printf("myfloor         %lf\n", reta);
        retb = floor(arg1);
        printf("libc floor      %lf\n", retb);
        printf("\n"); 

	//reta = myfactorial(arg1);
        //printf("myfactorial   %ld\n",(long) reta); 
        //printf("\n");

	retb = tgamma(arg1);
        printf("tgamma   %lf\n", retb);
        printf("\n");

	printf("ln(tgamma)   %lf\n", log(retb));
        printf("\n");

	retb = lgamma(arg1);
        printf("lgamma   %lf\n", retb); 
        printf("\n"); 

	retb = mygamma(arg1); 
        printf("mygamma   %lf\n", retb);
       

	retb = mygamma(arg1);
        printf("ln(mygamma)   %lf\n", log(retb));
	printf("ln(fabs(mygamma))   %lf\n", log(fabs(retb)));
        printf("\n");
	
	
	reta = mypow(arg1, arg2);
	printf("mypow         %lf\n", reta); 
	retb = pow(arg1, arg2);
	printf("libc pow      %lf\n", retb); 
	printf("\n");

	reta = myexp(arg1);
        printf("myexp         %lf\n", reta); 
        retb = exp(arg1);
        printf("libc exp      %lf\n", retb);
	printf("\n");

	reta = myfabs(arg1);
        printf("myfabs        %lf\n", reta); 
        retb = fabs(arg1);
        printf("libc fabs     %lf\n", retb); 
	printf("\n");

        reta = mylog(arg1);
        printf("mylog         %lf\n", reta); 
        retb = log(arg1); 
        printf("libc log      %lf\n", retb);
	printf("\n");

	reta = mysqrt(arg1);
        printf("mysqrt        %lf\n", reta); 
        retb = sqrt(arg1);
        printf("libc sqrt     %lf\n", retb); 
	printf("\n"); 

	reta = mysin(arg1);
        printf("mysin         %lf\n", reta); 
        retb = sin(arg1); 
        printf("libc sin      %lf\n", retb); 
	printf("\n");

	reta = mycos(arg1);
        printf("mycos         %lf\n", reta); 
        retb = cos(arg1);
        printf("libc cos      %lf\n", retb); 
	printf("\n"); 
	
	reta = mytan(arg1);
        printf("mytan         %lf\n", reta); 
	retb = tan(arg1);
        printf("libc tan      %lf\n", retb); 
	printf("\n"); 

	reta = myasin(arg1);
      	printf("myasin        %lf\n", reta); 
        retb = asin(arg1);
        printf("libc asin     %lf\n", retb); 
	printf("\n"); 

        reta = myacos(arg1);
        printf("myacos        %lf\n", reta); 
        retb = acos(arg1);
        printf("libc acos     %lf\n", retb); 
	printf("\n"); 

	reta =  myatan(arg1);
        printf("my atan       %lf\n", reta); 
        retb = atan(arg1);
        printf("libc atan     %lf\n", retb); 
	printf("\n");

	return 0; 

} 


