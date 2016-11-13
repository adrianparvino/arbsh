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
        double real_M = 0;
        double m_minus_M = 0; 
     
	if (argc < 4 )
	{
		fprintf(stderr, "Usage ./ast_calc -apparent-magnitude absolute-magnitude parsecs\n");
		return 1;
	}
   

        m = strtod(argv[1], 0);
        M = strtod(argv[2], 0);
	parsecs = strtod(argv[3], 0);

	
	
	printf("distance == %lf\n", log10(parsecs));
	printf("(m-M) == %lf\n", (((m - M) + 5) / 5)); 
	
	printf("After an extinction factor of %lf:\n", extinction_divisor);
	
	parsecs = log10(parsecs);
	m_minus_M = (((m - M) + 5) / 5);
	extinction = (( parsecs / extinction_divisor) * 1.8);
      
       
	printf("distance == %lf\n", parsecs - extinction);
        printf("(m-M) == %lf\n", m_minus_M);


        return 0;
}
