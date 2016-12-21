#include <stdio.h>  
#include <math.h>   /* for comparative testing */
#include <stdlib.h> /* for strtod */ 
#include <float.h>
#include <stdint.h>

#include "math.c" 


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
        printf("myj0         %19.19lf\n", reta); 

	retb = j0(arg1);
        printf("libc j0      %19.19lf\n", retb); 
        printf("\n");

	reta = myj1(arg1);
        printf("myj1         %19.19lf\n", reta); 

	retb = j1(arg1);
        printf("libc j1      %19.19lf\n", retb);
	printf("\n"); 
	
	reta = myjn(arg2, arg1); 
        printf("myjn         %19.19lf\n", reta); 
	retb = jnl(arg2, arg1);
        printf("libc jnl      %19.19lf\n", retb); 
        printf("\n"); 
      
        retb = rint(arg1);
        printf("libc rint      %19.19lf\n", retb);
	printf("\n"); 

	reta = myremainder(arg1, arg2); 
        printf("myremainder         %19.19lf\n", reta);
        retb = remainder(arg1, arg2);
        printf("libc remainder      %19.19lf\n", retb);
        printf("\n"); 

	reta = myhypot(arg1, arg2);
        printf("myhypot         %19.19lf\n", reta);
        retb = hypot(arg1, arg2);
        printf("libc hypot      %19.19lf\n", retb);
        printf("\n");
	
	reta = myceil(arg1);
        printf("myceil         %19.19lf\n", reta);
        retb = ceil(arg1);
        printf("libc ceil      %19.19lf\n", retb);
        printf("\n"); 

	reta = myfloor(arg1);
        printf("myfloor         %19.19lf\n", reta);
        retb = floor(arg1);
        printf("libc floor      %19.19lf\n", retb);
        printf("\n"); 

	reta = myfactorial(arg1);
        printf("myfactorial   %ld\n",(long) reta); 
        printf("\n");

	retb = tgamma(arg1);
        printf("tgamma   %19.19lf\n", retb);
        printf("\n");

	printf("ln(tgamma)   %19.19lf\n", log(retb));
        printf("\n");

	retb = lgamma(arg1);
        printf("lgamma   %19.19lf\n", retb); 
        printf("\n"); 

	retb = mygamma(arg1); 
        printf("mygamma   %19.19lf\n", retb);
       

	retb = mygamma(arg1);
        printf("ln(mygamma)   %19.19lf\n", log(retb));
	printf("ln(fabs(mygamma))   %19.19lf\n", log(fabs(retb)));
        printf("\n");
	
	
	reta = mypow(arg1, arg2);
	printf("mypow         %19.19lf\n", reta); 
	retb = pow(arg1, arg2);
	printf("libc pow      %19.19lf\n", retb); 
	printf("\n");

	reta = myexp(arg1);
        printf("myexp         %19.19lf\n", reta); 
        retb = exp(arg1);
        printf("libc exp      %19.19lf\n", retb);
	printf("\n");

	reta = myfabs(arg1);
        printf("myfabs        %19.19lf\n", reta); 
        retb = fabs(arg1);
        printf("libc fabs     %19.19lf\n", retb); 
	printf("\n");

        reta = mylog(arg1);
        printf("mylog         %19.19lf\n", reta); 
        retb = log(arg1); 
        printf("libc log      %19.19lf\n", retb);
	printf("\n");

	reta = mysqrt(arg1);
        printf("mysqrt        %19.19lf\n", reta); 
        retb = sqrt(arg1);
        printf("libc sqrt     %19.19lf\n", retb); 
	printf("\n"); 

	reta = mysin(arg1);
        printf("mysin         %19.19lf\n", reta); 
        retb = sin(arg1); 
        printf("libc sin      %19.19lf\n", retb); 
	printf("\n");

	reta = mycos(arg1);
        printf("mycos         %19.19lf\n", reta); 
        retb = cos(arg1);
        printf("libc cos      %19.19lf\n", retb); 
	printf("\n"); 
	
	reta = mytan(arg1);
        printf("mytan         %19.19lf\n", reta); 
	retb = tan(arg1);
        printf("libc tan      %19.19lf\n", retb); 
	printf("\n"); 

	reta = myasin(arg1);
      	printf("myasin        %19.19lf\n", reta); 
	//reta = myasin2(arg1);
        //printf("myasin2        %19.19lf\n", reta);
        retb = asin(arg1);
        printf("libc asin     %19.19lf\n", retb); 
	printf("\n"); 

        reta = myacos(arg1);
        printf("myacos        %19.19lf\n", reta); 
        retb = acos(arg1);
        printf("libc acos     %19.19lf\n", retb); 
	printf("\n"); 

	reta =  myatan(arg1);
        printf("my atan       %19.19lf\n", reta); 
        retb = atan(arg1);
        printf("libc atan     %19.19lf\n", retb); 
	printf("\n");

	reta =  myatanh(arg1);
       printf("my atanh       %19.19lf\n", reta);
        retb = atanh(arg1);
        printf("libc atanh     %19.19lf\n", retb);
        printf("\n");

	reta = mysinh(arg1);
        printf("mysinh        %19.19lf\n", reta); 
        retb = sinh(arg1);
        printf("libc sinh     %19.19lf\n", retb);
        printf("\n");
	
	reta = mycosh(arg1);
        printf("mycosh        %19.19lf\n", reta);
        retb = cosh(arg1);
        printf("libc cosh     %19.19lf\n", retb);
        printf("\n");

//	reta =  mytanh(arg1);
//        printf("my tan       %19.19lf\n", reta);
//        retb = tan(arg1);
//        printf("libc tan     %19.19lf\n", retb);
//        printf("\n");

	return 0; 

} 

