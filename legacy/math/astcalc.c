#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* (m-M) = distance in parsecs */
/* log10(d) = (((m - M) + 5) / 5) */



// polaris 1.98 -3.6 133 
// sun -26.74 4.83 0.000004848
int main(int argc, char *argv[])
{
        double m = 0;
        double M = 0;
        double parsecs = 0;
        double extinction_divisor = 1000;
	double extinction = 0;
        //double real_M = 0;
        double m_minus_M = 0; 
	double distance = 0;
	// d = 1/p
     
	if (argc < 4 )
	{
		fprintf(stderr, "Usage ./ast_calc apparent-magnitude absolute-magnitude parsecs\n");
		fprintf(stderr, "sample data\npolaris 1.98 -3.6 133\nsun -26.74 4.83 0.000004848 \n");

		return 1;
	}
   

        m = strtod(argv[1], 0);
        M = strtod(argv[2], 0);
	parsecs = strtod(argv[3], 0);
	m_minus_M = (((m - M) + 5) / 5);
	distance = log10(parsecs);
	
	
	printf("m                 = %20lf\n", m);
	printf("M                 = %20lf\n", M);
	printf("parsecs           = %20lf\n", parsecs);

	printf("distance (log(d)) = %20lf\n", distance);
	printf("(m-M)             = %20lf\n", m_minus_M);

	
	
	printf("After an extinction factor of %lf:\n", extinction_divisor);
	
	
	
	extinction = (( distance / extinction_divisor) * 1.8);
      
       
	printf("distance          = %20lf\n", distance - extinction);
        printf("(m-M)             = %20lf\n", m_minus_M);


        return 0;
}
